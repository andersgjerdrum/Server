#include <memory>
#include <atomic>

namespace MifuneCore
{
	/*
	Inspiration:
	http://www.drdobbs.com/parallel/writing-lock-free-code-a-corrected-queue/210604448
	http://www.drdobbs.com/parallel/writing-lock-free-code-a-corrected-queue/210604448?pgno=2
	*/
	template <typename T>
	struct CLFItem
	{
		CLFItem next;
		CLFItem prev;
		T Item;
	};

	class CLFQueue
	{
		std::atomic<std::shared_ptr<struct CLFItem>> head;
		std::atomic<std::shared_ptr<struct CLFItem>> tail;

	public:
		//Constructor is not threadsafe
		CLFQueue()
		{
			
		}

		template<typename T>
		void push(T& item)
		{
			auto p = make_shared<struct CLFItem>();
			p->item = item;
			p->next = head;
			p->prev =
		
		}
		template<typename T>
		T pop()
		{

		}
	};

}