#pragma once
#include "../LinkedList.hpp"

namespace DS {
	template<typename T, template <typename> class ListType = LinkedList>
	class LinkedListStack {
		ListType<T> stack;
	public:
		LinkedListStack() = default;

		LinkedListStack(const T& val) {
			stack.PushFront(val);
		}

		LinkedListStack(const LinkedListStack& Stack) {
			stack = ListType<T>(Stack.stack);
		}

		T& Top() {
			return stack.Tail()->value;
		}

		T Pop() {
			return stack.PopBack();
		}

		void Push(const T& val) {
			stack.PushBack(val);
		}

		int Size() {
			return stack.Size();
		}

		bool Empty() {
			return stack.Empty();
		}

		ListType<T>& List() {
			return stack;
		}
	};
}