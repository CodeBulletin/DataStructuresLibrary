#pragma once
#include "../Queues/PriorityQueue.hpp"

namespace HeapSort {
	template<typename T, int max_size, template <typename, int> class ArrayType = DS::Array>
	void HeapSort(ArrayType<T, max_size>& array) {
		DS::PriorityQueue<T, max_size, ArrayType> pQ;
		for (int i = 0; i < array.Size(); i++) {
			pQ.Insert(array[i]);
		}
		array.Clear();
		while (!pQ.Empty()) {
			array.PushBack(pQ.ExtractMax());
		}
		for (int i = 0; i < array.Size() / 2; i++) {
			array.Swap(i, array.Size() - i - 1);
		}
	}

	template<typename T, int max_size, template <typename, int> class ArrayType = DS::Array>
	void ShiftDown(int i, ArrayType<T, max_size>& Heap) {
		while (true) {
			int maxIndex = i;
			int l = 2 * i + 1;
			if (l < Heap.Size() && Heap[l] > Heap[maxIndex]) {
				maxIndex = l;
			}
			int r = 2 * i + 2;
			if (r < Heap.Size() && Heap[r] > Heap[maxIndex]) {
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

	template<typename T, int max_size, template <typename, int> class ArrayType = DS::Array>
	void BuildHeap(ArrayType<T, max_size>& Heap) {
		for (int j = Heap.Size() / 2; j >= 0; j--) {
			ShiftDown<T, max_size, ArrayType>(j, Heap);
		}
	}

	template<typename T, int max_size, template <typename, int> class ArrayType = DS::Array>
	void inPlaceHeapSort(ArrayType<T, max_size>& array) {
		BuildHeap<T, max_size, ArrayType>(array);
		int n = array.Size();
		for (int i = 0; i < n - 1; i++) {
			array.Swap(0, array.Size() - 1);
			array.setSize(array.Size() - 1);
			ShiftDown<T, max_size, ArrayType>(0, array);
		}
		array.setSize(n);
	}
}