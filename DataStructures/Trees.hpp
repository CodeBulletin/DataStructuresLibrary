#pragma once
#include "Trees/BalancedBT.hpp"
#include "Trees/BinarySearchTree.hpp"
#include "Trees/AVLTree.hpp"

namespace DS {
	template<typename T>
	using BalancedBST = AVLTree<T>;
}