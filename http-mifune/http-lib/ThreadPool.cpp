#pragma once

#include "threadpool.h"

namespace MifuneCore 
{

	class CancelationToken {
		std::shared_ptr<std::atomic<bool>> canceled;
	public:
		CancelationToken() :canceled(new std::atomic<bool>(false)) {}
		void Cancel() {canceled->store(true);}
		bool IsCanceled(void) {return canceled->load();}
	};
	class ThreadPool;

	class Worker {
	public:
		Worker(ThreadPool &s) : pool(s) {}
		void operator()();
		ThreadPool &pool;
	};

	class ThreadPool
	{
	public:
		Queue<std::function<void()>> queue;
		std::vector<std::thread> workers;
		bool stop;

		void scheduler()
		{
		}
		ThreadPool(int threads) : stop(false), queue(threads, threads)
		{
			for (int i = 0; i < threads; ++i)
			{
				workers.push_back(std::thread(Worker(*this)));

			}
		}
		~ThreadPool()
		{
			stop = true;

			//flush queue
			for (size_t i = 0; i < workers.size(); ++i)
			{
				queue.push([] {return; });
			}

			for (size_t i = 0; i < workers.size(); ++i)
			{
				workers[i].join();
			}
		}
		void enqueue(std::function<void()> f)
		{
			queue.push(f);
		}

	};

	void Worker::operator()() {

		std::function<void()> task;
		while (!pool.stop) {

			task = pool.queue.pop();
			task();
		}
	}
	

	
	/*class ThreadPool;

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
	}*/
}



