#pragma once
#include "../Trees/BalancedBT.hpp"

namespace DS {
	template<typename T, int max_size, template <typename, int> class ArrayType = Array>
	class PriorityQueue {
		BalancedBT<T, max_size, ArrayType> BBT;
	public:
		PriorityQueue() = default;

		PriorityQueue(const PriorityQueue & pQ) {
			BBT = BalancedBT<T, max_size, ArrayType>(pQ.BBT);
		}

		void Insert(const T& val) {
			BBT.Insert(val);
		}

		T& ExtractMax() {
			return BBT.Extract();
		}

		int Size() {
			return BBT.Size();
		}

		bool Empty() {
			return BBT.Empty();
		}

		BalancedBT<T, max_size, ArrayType>& BalancedBinaryTree() {
			return BBT;
		}

		int MaxSize() {
			return BBT.MaxSize();
		}
	};
}