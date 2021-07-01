#pragma once
#include "../Array.hpp"

namespace DS {
	template <typename T, int max_size, template<typename, int> class ArrayType = Array>
	class BalancedBT {
		ArrayType<T, max_size> Heap;
	public:
		BalancedBT() = default;

		BalancedBT(const BalancedBT& BST) {
			Heap = ArrayType<T, max_size>(BST.Heap);
		}

		int Parent(int i) {
			return i / 2;
		}

		int LeftChild(int i) {
			return 2 * i + 1;
		}

		int RightChild(int i) {
			return 2 * i + 2;
		}

		void ShiftUP(int i) {
			while (i > 0 and Heap[Parent(i)] < Heap[i]) {
				Heap.Swap(Parent(i), i);
				i = Parent(i);
			}
		}

		void ShiftDown(int i) {
			while (true) {
				int maxIndex = i;
				int l = LeftChild(i);
				if (l < Size() && Heap[l] > Heap[maxIndex]) {
					maxIndex = l;
				}
				int r = RightChild(i);
				if (r < Size() && Heap[r] > Heap[maxIndex]) {
					maxIndex = r;
				}
				if (i != maxIndex) {
					Heap.Swap(i, maxIndex);
					i = maxIndex;
				}
				else {
					break;
				}
			}
		}

		void Insert(const T& p) {
			Heap.PushBack(p);
			ShiftUP(Size() - 1);
		}

		T& Extract() {
			Heap.Swap(0, Size() - 1);
			T& result = Heap[Size() - 1];
			Heap.setSize(Size() - 1);
			ShiftDown(0);
			return result;
		}

		T& operator[](int i) {
			return Heap[i];
		}

		int Size() {
			return Heap.Size();
		}

		bool Empty() {
			return Heap.Size() == 0;
		}

		ArrayType<T, max_size>& Array() {
			return Heap;
		}

		int MaxSize() {
			return Heap.MaxSize();
		}
	};
}