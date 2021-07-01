#pragma once
#include <memory>

namespace DS {
	template<typename T>
	struct DLLNode {
		T value;
		std::shared_ptr<DLLNode<T>> next;
		std::shared_ptr<DLLNode<T>> prev;
	};

	template<typename T>
	struct SLLNode {
		T value;
		std::shared_ptr<SLLNode<T>> next;
	};

	template<typename T>
	struct AVLNode {
		T value = {};
		std::shared_ptr<AVLNode<T>> Left = nullptr, Right = nullptr, Parent = nullptr;
		int Height;
	};

	template<typename T>
	struct BSTNode {
		T value = {};
		std::shared_ptr<BSTNode<T>> Left = nullptr, Right = nullptr, Parent = nullptr;
	};
}