#pragma once
#include "../Array.hpp"

namespace DS {
	template<typename T, int max_size, template <typename, int> class ArrayType = Array>
	class StaticArrayQueue {
		ArrayType<T, max_size + 1> queue;
		int rd = 0, wr = 0;
	public:
		StaticArrayQueue() : queue(max_size + 1), wr(0), rd(0) {
		}

		StaticArrayQueue(const T& val) : queue(max_size + 1), wr(0), rd(0) {
			queue[wr] = val;
			wr++;
		}

		StaticArrayQueue(const StaticArrayQueue& Queue) {
			queue = ArrayType<T, max_size + 1>(Queue.queue);
			rd = Queue.rd;
			wr = Queue.wr;
		}

		void Enqueue(const T& val) {
			int w1 = (wr + 1) % (max_size + 1);
			if (rd - (w1 - 1) != 1) {
				queue[wr] = val;
				wr = w1;
			}
			else {
				throw std::out_of_range("Queue is full");
			}
		}

		T Dequeue() {
			int r1 = rd;
			rd = (rd + 1) % (max_size + 1);
			return queue[r1];
		}

		int Size() {
			if (rd <= wr) {
				return wr - rd;
			}
			else {
				return (max_size - rd + 1) + wr;
			}
		}

		bool Empty() {
			return rd == wr;
		}

		ArrayType<T, max_size + 1>& Array() {
			return queue;
		}

		int MaxSize() {
			return max_size;
		}
	};
}