#pragma once
#include "LinkedLists/CircularlyLinkedList.hpp"
#include "LinkedLists/SinglyLinkedList.hpp"
#include "LinkedLists/DoublyLinkedList.hpp"

namespace DS {
	template<typename T>
	using LinkedList = DoublyLinkedList<T>;
}