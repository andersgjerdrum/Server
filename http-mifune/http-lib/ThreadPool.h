#pragma once
#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "queue.h"
#include <vector>
#include <thread>
#include <atomic>
#endif



namespace MifuneCore
{

	class CancelationToken {
		std::shared_ptr<std::atomic<bool>> canceled;
	public:
		CancelationToken() :canceled(new std::atomic<bool>(false)) {}
		void Cancel() { canceled->store(true); }
		bool IsCanceled(void) { return canceled->load(); }
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
				//Noop task
				queue.push(nullptr);
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
			if (task == nullptr)
				break;
			task();
		}
	}
}