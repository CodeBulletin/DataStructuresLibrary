#pragma once
#include "../LinkedList.hpp"

namespace DS {
	template<typename T, template <typename> class ListType = LinkedList>
	class LinkedListQueue {
		ListType<T> queue;
	public:
		LinkedListQueue() = default;

		LinkedListQueue(const T& val) {
			queue.PushFront(val);
		}

		LinkedListQueue(const LinkedListQueue& Queue) {
			queue = ListType<T>(Queue.queue);
		}

		void Enqueue(const T& val) {
			queue.PushBack(val);
		}

		T Dequeue() {
			return queue.PopFront();
		}

		int Size() {
			return queue.Size();
		}

		bool Empty() {
			return queue.Empty();
		}

		ListType<T>& List() {
			return queue;
		}
	};
}