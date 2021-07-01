#pragma once

#include "../Nodes.hpp"
#include <functional>
#include <stdexcept>

namespace DS {
	template<typename T>
	class CircularlyLinkedList {
	private:
		std::shared_ptr<DLLNode<T>> head = nullptr;
		int size = 0;

	public:
		CircularlyLinkedList() = default;

		CircularlyLinkedList(T Val) {
			head = std::make_shared<DLLNode<T>>(new DLLNode<T>());
			head->value = Val;
			head->next = head;
			head->prev = head;
			size++;
		}

		CircularlyLinkedList(const CircularlyLinkedList<T>& list) {
			if (!list.head) return;
			std::shared_ptr<DLLNode<T>> Next = list.head;
			do {
				PushBack(Next->value);
				Next = Next->next;
			} while (Next->next != list.head);
		}

		~CircularlyLinkedList() {
			Clear();
		}

		void Clear() {
			if (!head) return;
			std::shared_ptr<DLLNode<T>> current_ptr = head;
			do
			{
				head = current_ptr->next;
				current_ptr->next = nullptr;
				current_ptr = head;
			} while (current_ptr != head);
			head = nullptr;
			size = 0;
		}

		void PushFront(const T& value) {
			std::shared_ptr<DLLNode<T>> new_node(new DLLNode<T>());
			if (!head) {
				head = new_node;
				head->value = value;
				head->next = head;
				head->prev = head;
				size++;
				return;
			}
			new_node->value = value;
			new_node->next = head;
			new_node->prev = head->prev;
			head->prev->next = new_node;
			head->prev = new_node;
			head = new_node;
			size++;
		}

		void PushBack(const T& value) {
			std::shared_ptr<DLLNode<T>> new_node(new DLLNode<T>());
			if (!head) {
				head = new_node;
				head->value = value;
				head->next = head;
				head->prev = head;
				size++;
				return;
			}
			new_node->value = value;
			new_node->next = head;
			new_node->prev = head->prev;
			head->prev->next = new_node;
			head->prev = new_node;
			size++;
		}

		void PushAfter(std::shared_ptr<DLLNode<T>> Node, const T& value) {
			std::shared_ptr<DLLNode<T>> new_node(new DLLNode<T>());
			new_node->value = value;
			new_node->next = Node->next;
			Node->next->prev = new_node;
			Node->next = new_node;
			new_node->prev = Node;
			size++;
		}

		void PushBefore(std::shared_ptr<DLLNode<T>> Node, const T& value) {
			std::shared_ptr<DLLNode<T>> new_node(new DLLNode<T>());
			new_node->value = value;
			new_node->next = Node;
			Node->prev->next = new_node;
			new_node->prev = Node->prev;
			Node->prev = new_node;
			size++;
		}

		T PopFront() {
			std::shared_ptr<DLLNode<T>> Node = head;
			if (head->next == head) {
				head->next = nullptr;
				head->prev = nullptr;
				head = nullptr;
				size = 0;
				return Node->value;
			}
			head->next->prev = head->prev;
			head->prev->next = head->next;
			head = head->next;
			size -= 1;
			return Node->value;
		}

		T PopAfter(std::shared_ptr<DLLNode<T>> Node) {
			std::shared_ptr<DLLNode<T>> nNode = Node->next;
			if (Node == nNode) {
				head->next = nullptr;
				head->prev = nullptr;
				head = nullptr;
				size = 0;
				return Node->value;
			}
			std::shared_ptr<DLLNode<T>> nnNode = Node->next->next;
			nnNode->prev = Node;
			Node->next = nnNode;
			size -= 1;
			return nNode->value;
		}

		T PopBefore(std::shared_ptr<DLLNode<T>> Node) {
			if (head->next == Node) {
				return PopBack();
			}

			std::shared_ptr<DLLNode<T>> pNode = Node->prev;

			std::shared_ptr<DLLNode<T>> ppNode = pNode->prev;
			ppNode->next = Node;
			Node->prev = ppNode;
			pNode->next = nullptr;
			pNode->prev = nullptr;

			size -= 1;
			return pNode->value;
		}

		T PopBack() {
			return PopBefore(head);
		}

		T Pop(std::shared_ptr<DLLNode<T>> Node) {
			Node->prev->next = Node->next;
			Node->next->prev = Node->prev;
			Node->next = nullptr;
			Node->prev = nullptr;
			return Node->value;
		}

		std::shared_ptr<DLLNode<T>> GetNodeAt(int n) {
			if (n < 0 || n >= size) {
				return nullptr;
			}

			std::shared_ptr<DLLNode<T>> Node = head;
			for (int i = 0; i < n; i++) {
				Node = Node->next;
			}
			return Node;
		}

		std::shared_ptr<DLLNode<T>> operator[](int n) {
			return GetNodeAt(n);
		}

		std::shared_ptr<DLLNode<T>> find(const T& Val) {
			if (!head) return nullptr;
			std::shared_ptr<DLLNode<T>> Node = head;
			do {
				if (Node->value == Val) {
					return Node;
				}
				Node = Node->next;
			} while (Node != head);
			return nullptr;
		}

		template<typename T2>
		std::shared_ptr<DLLNode<T>> findBy(const T2& Val) {
			if (!head) return nullptr;
			std::shared_ptr<DLLNode<T>> Node = head;
			do {
				if (Node->value == Val) {
					return Node;
				}
				Node = Node->next;
			} while (Node != head);
			return nullptr;
		}

		bool Empty() {
			return size == 0;
		}

		int Size() {
			return size;
		}

		std::shared_ptr<DLLNode<T>> Head() {
			return head;
		}

		std::shared_ptr<DLLNode<T>> Tail() {
			return head->prev;
		}
	};
}
