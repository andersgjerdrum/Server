#include "ThreadPool.h"
namespace MifuneCore 
{

	void Worker::operator()() 
	{
		std::function<void()> task;
		while (true) 
		{
			{
				std::unique_lock<std::mutex> 
					lock(pool.queue_mutex);
				while(!pool.stop && pool.tasks.empty())
				{
					pool.condition.wait(lock, [&]() {
						return !(pool.tasks.size() == 0 && !pool.stop);
					});;
				}
				if (pool.stop)
					return;
				task = pool.tasks.front();
				pool.tasks.pop_front();

			}

			task();
		}
	}
	ThreadPool::ThreadPool(size_t threads) : stop(false)
	{
		for (size_t i = 0; i < threads; ++i) 
		{
			workers.push_back(std::thread(Worker(*this)));
		}
	}
	ThreadPool::~ThreadPool() 
	{
		stop = true;
		condition.notify_all();
		for (size_t i = 0;i < workers.size(); ++i) 
		{
			workers[i].join();
		}
	}

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