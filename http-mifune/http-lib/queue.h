
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
	

	class ThrPos
	{
	public:
		unsigned long head, tail;
		ThrPos(): head(ULONG_MAX), tail(ULONG_MAX){}
	};

	template<class T>
	class Queue 
	{
	private:
		const size_t n_producers_, n_consumers_;
		unsigned long	head_;
		unsigned long	tail_;
		unsigned long	last_head_;
		unsigned long	last_tail_;
		unsigned long thrd_next;
		std::vector<ThrPos>	thr_p_;
		std::vector<T>	ptr_array_;
		static const unsigned long Q_MASK = Q_SIZE - 1;
		
	public:
		Queue(size_t n_producers, size_t n_consumers)
			: n_producers_(n_producers),
			n_consumers_(n_consumers),
			head_(0),
			tail_(0),
			last_head_(0),
			last_tail_(0),
			ptr_array_(Q_SIZE),
			thr_p_(max(n_consumers_, n_producers_) + 2),
			thrd_next(0)
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

			while ((thr_pos().head >= last_tail_ + Q_SIZE) != 0)
			{
				auto min = tail_;

				for (size_t i = 2; i < n_consumers_ + 2; ++i) {
					auto tmp_t = thr_p_[i].tail;

					// Force compiler to use tmp_h exactly once.
					std::atomic_thread_fence(std::memory_order_acquire);
					std::atomic_thread_fence(std::memory_order_release);

					if (tmp_t < min)
						min = tmp_t;
				}
				last_tail_ = min;

				if (thr_pos().head < last_tail_ + Q_SIZE)
					break;
				_mm_pause();
			}

			ptr_array_[thr_pos().head & Q_MASK] = ptr;

			thr_pos().head = ULONG_MAX;
		}

		T pop()
		{
			
			thr_pos().tail = tail_;
			thr_pos().tail = atomic_inc(&tail_);

			while ((thr_pos().tail >= last_head_) != 0)
			{
				auto min = head_;

				for (size_t i = 2; i < n_producers_ + 2; ++i) {
					auto tmp_h = thr_p_[i].head;

					// Force compiler to use tmp_h exactly once.
					std::atomic_thread_fence(std::memory_order_acquire);
					std::atomic_thread_fence(std::memory_order_release);

					if (tmp_h < min)
						min = tmp_h;
				}
				last_head_ = min;

				if (thr_pos().tail < last_head_)
					break;
				_mm_pause();
			}

			T ret = ptr_array_[thr_pos().tail & Q_MASK];
 			thr_pos().tail = ULONG_MAX;
			return ret;
		}

	
	};
}