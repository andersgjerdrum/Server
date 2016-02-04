
#pragma once
#include <limits.h>
#include <string.h>
#include <immintrin.h>
#include <Windows.h>
#include <assert.h>    
#include <atomic>
#include <condition_variable>
#include <thread>
#include <vector>
#include <map>
#define Q_SIZE	(32 * 1024)

#define atomic_inc(ptr) InterlockedIncrement ((ptr))
__declspec(thread) unsigned long tls_i = ULONG_MAX;



namespace MifuneCore
{
/**
* @return continous thread IDs starting from 0 as opposed to pthread_self().
*/
	


struct ThrPos {
	volatile unsigned long head = ULONG_MAX, tail = ULONG_MAX;
};
	template<class T>
	class Queue 
	{
	private:
		const size_t n_producers_, n_consumers_;
		unsigned long	head_;
		unsigned long	tail_;
		volatile unsigned long last_head_;
		volatile unsigned long last_tail_;
		volatile unsigned long thrd_next;
		std::vector<T>	ptr_array_;
		static const unsigned long Q_MASK = Q_SIZE - 1;
		std::condition_variable cond_empty_;
		std::condition_variable cond_overflow_;
		std::mutex mtx_;
		std::vector<ThrPos> thr_p_;
	

	public:
		Queue(size_t n_producers, size_t n_consumers)
			: n_producers_(n_producers),
			n_consumers_(n_consumers),
			head_(0),
			tail_(0),
			last_head_(0),
			last_tail_(0),
			thrd_next(0),
			ptr_array_(Q_SIZE),
			thr_p_(max(n_consumers, n_producers) + 2)
		{
		}
		ThrPos&	thr_pos()
		{
			if (tls_i == ULONG_MAX)
			{
				tls_i = atomic_inc(&thrd_next);
			}

			assert(tls_i < max(n_consumers_, n_producers_) + 2);
			return thr_p_[tls_i];
		}
	
		void push(T ptr)
		{
			thr_pos().head = head_;
			thr_pos().head = atomic_inc(&head_);

			while (thr_pos().head >= (last_tail_ + Q_SIZE))
			{
				std::this_thread::yield();

				auto min = tail_;
				for (size_t i = 0; i < n_consumers_ + 2; ++i) {
					auto tmp_t = thr_p_[i].tail;

					_ReadWriteBarrier(); // compiler barrier

					if (tmp_t < min)
						min = tmp_t;
				}
				last_tail_ = min;
			}

			ptr_array_[thr_pos().head & Q_MASK] = ptr;
			thr_pos().head = ULONG_MAX;
		}


		T pop()
		{
			thr_pos().tail = tail_;
			thr_pos().tail = atomic_inc(&tail_);

			while (thr_pos().tail > last_head_)
			{
				std::this_thread::yield();

				auto min = head_;
				for (size_t i = 0; i < n_producers_ + 2; ++i) {
					auto tmp_h = thr_p_[i].head;

					_ReadWriteBarrier(); // compiler barrier

					if (tmp_h < min)
						min = tmp_h;
				}
				last_head_ = min;
			}

			T ret = ptr_array_[thr_pos().tail & Q_MASK];
			thr_pos().tail = ULONG_MAX;
			return ret;
		}

	
	};
}