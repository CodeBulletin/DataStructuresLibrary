#pragma once
#include "Arrays/StaticArray.hpp"
#include "Arrays/DynamicArray.hpp"

namespace DS {
	template<typename T, int max_size>
	using Array = StaticArray<T, max_size>;

	template<typename T, int max_size = 1>
	using ArrayList = DynamicArray<T, max_size>;
}