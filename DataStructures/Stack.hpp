#pragma once
#include "Stacks/ArrayStack.hpp"
#include "Stacks/LinkedListStack.hpp"

namespace DS {
	template <typename T>
	using Stack = LinkedListStack<T>;

	template <typename T, int max_size>
	using StaticStack = ArrayStack<T, max_size, Array>;

	template <typename T, int max_size = 1>
	using DynamicStack = ArrayStack<T, max_size, ArrayList>;
}