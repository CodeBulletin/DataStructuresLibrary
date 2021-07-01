#pragma once
#include "../LinkedList.hpp"
#include "../Array.hpp"

namespace DS {
	template <typename key, typename val, template <typename> class HashFunction = std::hash,
		int max_size = 1, template <typename> class ListType = LinkedList>
	class HashMap {
	public:
		template<typename _key = key, typename _val = val>
		struct Pair {
			_key Key;
			_val Val;

			bool operator==(const _key& _key_) {
				return Key == _key_;
			}
		};

	private:
		HashFunction<key> Hash{};
		int M = max_size;
		int size = 0;

		std::unique_ptr<ListType<Pair<key, val>>[]> KeyVal =
			std::make_unique<ListType<Pair<key, val>>[]>(max_size);

		ArrayList<key*> Keys;

	public:
		HashMap() = default;
		HashMap(const HashMap& map) : Hash(map.Hash), M(map.M), size(map.size) {
			for (int i = 0; i < Size; i++) {
				auto next = map.KeyVal[i].Head();
				int HashVal = Hash(next.get()->value.Key);
				while (next)
				{
					KeyVal[HashVal].PushFront({ next.get()->value.Key, next.get()->value.Val });
					next = next->next;
				}
			}
		}

		void Insert(const key& Key, const val& Val) {
			if (!Find(Key)) {
				KeyVal[Hash(Key) % M].PushFront({ Key,  Val });
				float loadFactor = size / (float)M;
				if (loadFactor > 0.9) {
					Rehash();
				}
				size++;
			}
		}

		void Insert(const Pair<key, val>& pair) {
			if (!Find(pair.Key)) {
				KeyVal[Hash(pair.Key) % M].PushFront({ pair.Key, pair.Val });
				float loadFactor = size / (float)M;
				if (loadFactor > 0.9) {
					Rehash();
				}
				size++;
			}
		}

		Pair<key, val> Remove(const key& Key) {
			auto& List = KeyVal[Hash(Key) % M];
			auto it = List.findBy(Key);
			if (it) {
				size--;
				return List.Pop(it);
			}
			throw std::out_of_range("Key not found");
		}

		val& Get(const key& Key) {
			auto& List = KeyVal[Hash(Key) % M];
			auto it = List.findBy(Key);
			if (it) {
				return it->value.Val;
			}
			throw std::out_of_range("Key not found");
		}

		Pair<key, val>& GetPair(const key& Key) {
			auto& List = KeyVal[Hash(Key) % M];
			auto it = List.findBy(Key);
			if (it) {
				return it->value;
			}
			throw std::out_of_range("Key not found");
		}

		bool Find(const key& Key) {
			auto& List = KeyVal[Hash(Key) % M];
			auto it = List.findBy(Key);
			if (it) {
				return true;
			}
			return false;
		}

		val& operator[](const key& Key){
			auto& List = KeyVal[Hash(Key) % M];
			auto it = List.findBy(Key);
			if (it) {
				return it->value.Val;
			}
			throw std::out_of_range("Key not found");
		}

		void Rehash() {
			M *= 2;
			std::unique_ptr<ListType<Pair<key, val>>[]> Temp =
				std::make_unique<ListType<Pair<key, val>>[]>(M);
			for (int i = 0; i < size; i++) {
				auto next = KeyVal[i].Head();
				while (next)
				{
					Temp[Hash(next->value.Key) % M].PushFront({
						next->value.Key,
						next->value.Val
					});
					next = next->next;
				}
			}
			std::swap(Temp, KeyVal);
			Temp.release();
		}

		ArrayList<key*>& AllKeys() {
			Keys.Clear();
			for (int i = 0; i < size; i++) {
				auto next = KeyVal[i].Head();
				while (next)
				{
					Keys.PushBack(&next->value.Key);
					next = next->next;
				}
			}
			return Keys;
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

		int HashKey(const key& Key) {
			return Hash(Key);
		}
	};
}