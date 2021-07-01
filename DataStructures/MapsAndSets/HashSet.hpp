#pragma once
#include "../LinkedList.hpp"
#include "../Array.hpp"

namespace DS {
	template <typename T, template <typename> class HashFunction = std::hash, int max_size = 1,
		template <typename> class ListType = LinkedList>
	class HashSet {
	private:
		HashFunction<T> Hash{};
		int M = max_size;
		int size = 0;

		std::unique_ptr<ListType<T>[]> Vals = std::make_unique<ListType<T>[]>(max_size);
		ArrayList<T*> ValsPtr;
	public:
		HashSet() = default;
		HashSet(const HashSet& set) : Hash(set.Hash), M(set.M), size(set.size) {
			for (int i = 0; i < size; i++) {
				auto next = set.Vals[i].Head();
				int HashVal = Hash(next.get()->value);
				while (next)
				{
					Vals[HashVal].PushFront(next.get()->value);
					next = next->next;
				}
			}
		}

		void Insert(const T& Value) {
			if (!Find(Value)) {
				Vals[Hash(Value) % M].PushFront(Value);
				float loadFactor = size / (float)M;
				if (loadFactor > 0.9) {
					Rehash();
				}
				size++;
			}
		}

		T Remove(const T& Value) {
			auto& List = Vals[Hash(Value) % M];
			auto it = List.find(Value);
			if (it) {
				size--;
				return List.Pop(it);
			}
			throw std::out_of_range("Value not found");
		}

		bool Find(const T& Value) {
			auto& List = Vals[Hash(Value) % M];
			auto it = List.find(Value);
			if (it) {
				return true;
			}
			return false;
		}

		const T& Get(const T& Value) {
			auto& List = Vals[Hash(Value) % M];
			auto it = List.find(Value);
			if (it) {
				return it->value;
			}
			throw std::out_of_range("Value not found");
		}

		const T& operator[](const T& Value) {
			auto& List = Vals[Hash(Value) % M];
			auto it = List.find(Value);
			if (it) {
				return it->value;
			}
			throw std::out_of_range("Value not found");
		}

		void Rehash() {
			M *= 2;
			std::unique_ptr<ListType<T>[]> Temp = std::make_unique<ListType<T>[]>(M);
			for (int i = 0; i < size; i++) {
				auto next = Vals[i].Head();
				while (next)
				{
					Temp[Hash(next->value) % M].PushFront(next->value);
					next = next->next;
				}
			}
			std::swap(Temp, Vals);
			Temp.release();
		}

		ArrayList<T*>& AllVals() {
			ValsPtr.Clear();
			for (int i = 0; i < size; i++) {
				auto next = Vals[i].Head();
				while (next)
				{
					ValsPtr.PushBack(&next->value);
					next = next->next;
				}
			}
			return ValsPtr;
		}

		int Size() {
			return size;
		}

		int ArraySize() {
			return M;
		}

		bool Empty() {
			return size == 0;
		}

		int HashKey(const T& Value) {
			return Hash(Value);
		}

		void Union(const HashSet& set) {
			for (int i = 0; i < set.M; i++) {
				auto next = set.Vals[i].Head();
				while (next)
				{
					Insert(next.get()->value);
					next = next->next;
				}
			}
		}

		void Intersection(HashSet& set) {
			for (int i = 0; i < M; i++) {
				auto next = Vals[i].Head();
				while (next)
				{
					if (!set.Find(next->value)) {
						Remove(next->value);
					}
					next = next->next;
				}
			}
		}
	};
}