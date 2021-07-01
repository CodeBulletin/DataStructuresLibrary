#pragma once
#include "Queues/StaticArrayQueue.hpp"
#include "Queues/LinkedListQueue.hpp"
#include "Queues/PriorityQueue.hpp"

namespace DS {
	template <typename T>
	using Queue = LinkedListQueue<T>;

	template <typename T, int max_size>
	using StaticQueue = StaticArrayQueue<T, max_size>;
}