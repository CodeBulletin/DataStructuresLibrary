#pragma once
#include <memory>
#include <stdexcept>

namespace DS {
	template<typename T, int max = 1>
	class DynamicArray {
		std::unique_ptr<T[]> elements = std::make_unique<T[]>(max);
		int max_size = max;
		int size = 0;
	public:
		DynamicArray() = default;

		DynamicArray(int size) : size(size) {}

		DynamicArray(const DynamicArray<T>& array) {
			size = array.size;
			elements = std::make_unique<T[]>(array.max_size);
			for (int i = 0; i < size; i++) {
				elements[i] = array.elements[i];
			}
		}

		~DynamicArray() {
			elements.reset();
		}

		T& operator[](int n) {
			if (n < size && n >= 0) {
				return elements[n];
			}
			throw std::out_of_range("Index out of Range");
		}

		void PushBack(const T& item) {
			if (size == max_size) {
				Resize(size * 2);
			}
			elements[size] = item;
			size++;
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

		void PushAt(T item, int location) {
			if (size == max_size) {
				Resize(size * 2);
			}
			size++;
			for (int i = size - 1; i >= location; i--) {
				elements[i] = elements[i - 1];
			}
			elements[location] = item;
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

		std::unique_ptr<T[]>& Elements() {
			return elements;
		}

		void Resize(int _size) {
			std::unique_ptr<T[]> copy = std::make_unique<T[]>(_size);
			size = std::min(_size, size);
			for (int i = 0; i < size; i++) {
				copy.get()[i] = elements[i];
			}
			elements.reset();
			elements.swap(copy);
			max_size = _size;
		}
	};
}