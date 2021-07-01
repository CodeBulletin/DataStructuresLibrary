#pragma once
#include "HashMap.hpp"

namespace DS {
	template <typename T, template <typename> class HashFunction = std::hash,
		int max_size = 1, template <typename> class ListType = LinkedList>
	class DisjointSet {
	private:
		HashMap<T, T, HashFunction, max_size, ListType> Parent;
		HashMap<T, int, std::hash, max_size, ListType> Rank;
	public:
		DisjointSet() = default;
		DisjointSet(const DisjointSet& disjointSet) : Parent(disjointSet.Parent), 
		Rank(disjointSet.Rank) {}

		void MakeSet(const T& Value) {
			Parent.Insert(Value, Value);
			Rank.Insert(Value, 0);
		}

		T Find(T Val) {
			if (!(Val==Parent[Val]))
			{
				Parent[Val] = Find(Parent[Val]);
			}
			return Parent[Val];
		}

		void Union(T Val1, T Val2) {
			T v1_p = Find(Val1);
			T v2_p = Find(Val2);
			if (v1_p == v2_p) return;
			if (Rank[v1_p] > Rank[v2_p]) {
				Parent[v2_p] = v1_p;
				return;
			}
			Parent[v1_p] = v2_p;
			if (Rank[v1_p] == Rank[v2_p]) Rank[v2_p] += 1;
		}

		void CompressSets() {
			auto& keys = Parent.AllKeys();
			for (int i = 0; i < keys.Size(); i++) {
				Find(*keys[i]);
			}
		}
	};
}