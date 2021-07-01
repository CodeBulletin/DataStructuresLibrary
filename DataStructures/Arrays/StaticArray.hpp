#pragma once
#include <stdexcept>

namespace DS {
	template<typename T, int Max_size>
	class StaticArray {
		T elements[Max_size] = {};
		int max_size = Max_size;
		int size = 0;
	public:
		StaticArray() = default;

		StaticArray(int _size) {
			size = _size;
		}

		StaticArray(const StaticArray<T, Max_size>& array) {
			size = array.size;
			for (int i = 0; i < size; i++) {
				elements[i] = array.elements[i];
			}
		}

		T& operator[](int n) {
			if (n < size && n >= 0) {
				return elements[n];
			}
			throw std::out_of_range("Index out of Range");
		}

		bool PushBack(const T& item) {
			if (size != max_size) {
				elements[size] = item;
				size++;
				return true;
			}
			return false;
		}

		T PopBack() {
			if (size > 0) {
				size -= 1;
				return elements[size];
			}
			else {
				throw std::out_of_range("Array is empty");
			}
		}

		bool PushAt(T item, int location) {
			if (size != max_size) {
				size++;
				for (int i = size - 1; i >= location; i--) {
					elements[i] = elements[i - 1];
				}
				elements[location] = item;
				return true;
			}
			return false;
		}

		T PopAt(int location) {
			if (size > 0) {
				if (location >= 0 && location < size) {
					T& item = elements[location];
					for (int i = location; i < size; i++) {
						elements[i] = elements[i + 1];
					}
					size--;
					return item;
				}
				throw std::out_of_range("Index out of range");
			}
			throw std::out_of_range("Array is empty");
		}

		int MaxSize() {
			return max_size;
		}

		void MaxSize(int _max_size) {
			max_size = _max_size;
		}

		int Size() {
			return size;
		}

		void setSize(int n) {
			size = n;
		}

		void Clear() {
			size = 0;
		}

		void Swap(int i1, int i2) {
			std::swap(elements[i1], elements[i2]);
		}
	};
}