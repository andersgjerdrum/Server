#pragma once
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace MifuneCore {
	class ThreadPool;

	class Worker {
	public:
		Worker(ThreadPool &s) : pool(s) {}
		void operator()();
		ThreadPool &pool;
	};

	class ThreadPool {
	public:
		ThreadPool(size_t);
		template<class F>
		void enqueue(F f);
		~ThreadPool();
	private:
		friend class Worker;

		std::vector<std::thread> workers;
		std::deque<std::function<void()>> tasks;
		std::mutex queue_mutex;
		std::condition_variable condition;
		bool stop;
	};

	template<class F>
	void ThreadPool::enqueue(F f)
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			tasks.push_back(std::function<void()>(f));
		}

		condition.notify_one();
	}
}