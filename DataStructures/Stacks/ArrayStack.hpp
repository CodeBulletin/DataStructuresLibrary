#pragma once
#include "../Array.hpp"

namespace DS {
	template<typename T, int max_size = 1, template <typename, int> class ArrayType = Array>
	class ArrayStack {
		ArrayType<T, max_size> stack;
	public:
		ArrayStack() = default;

		ArrayStack(const T& val) {
			stack.PushBack(val);
		}

		ArrayStack(const ArrayStack& Stack) {
			stack = ArrayType<T, max_size>(Stack.stack);
		}

		T& Top() {
			return stack[stack.Size() - 1];
		}

		T Pop() {
			return stack.PopBack();
		}

		void Push(const T& val) {
			if (stack.Size() <= max_size) {
				stack.PushBack(val);
			}
			else {
				throw std::out_of_range("Stack is full");
			}
		}

		int Size() {
			return stack.Size();
		}

		bool Empty() {
			return stack.Size() == 0;
		}

		ArrayType<T, max_size>& Array() {
			return stack;
		}

		int MaxSize() {
			return max_size;
		}
	};
}