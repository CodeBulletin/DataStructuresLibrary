#pragma once
#include "../Nodes.hpp"
#include <functional>
#include <stdexcept>

namespace DS {
	template<typename T = int>
	class SinglyLinkedList {
	private:
		std::shared_ptr<SLLNode<T>> head = nullptr, tail = nullptr;
		int size = 0;

	public:
		SinglyLinkedList() = default;

		SinglyLinkedList(T Val) {
			tail = head = std::make_shared<SLLNode<T>>(new SLLNode<T>());
			head->value = Val;
			size++;
		}

		SinglyLinkedList(const SinglyLinkedList& list) {
			std::shared_ptr<SLLNode<T>> Next = list.head;
			while (Next) {
				PushBack(Next->value);
				Next = Next->next;
			}
		}

		~SinglyLinkedList() {
			Clear();
		}

		void Clear() {
			std::shared_ptr<SLLNode<T>> current_ptr = head;
			while (current_ptr)
			{
				head = current_ptr->next;
				current_ptr = head;
			}
			head = tail = nullptr;
			size = 0;
		}

		void PushFront(const T& value) {
			if (!head) {
				PushBack(value);
				return;
			}
			std::shared_ptr<SLLNode<T>> new_node(new SLLNode<T>());
			new_node->value = value;
			new_node->next = head;
			head = new_node;
			if (!head->next) {
				tail = head;
			}
			size++;
		}

		void PushAfter(std::shared_ptr<SLLNode<T>> Node, const T& value) {
			std::shared_ptr<SLLNode<T>> new_node(new SLLNode<T>());
			new_node->value = value;
			new_node->next = Node->next;
			Node->next = new_node;
			if (Node == tail) {
				tail = new_node;
			}
			size++;
		}

		void PushBack(const T& value) {
			std::shared_ptr<SLLNode<T>> new_node(new SLLNode<T>());
			new_node->value = value;
			if (!tail) {
				tail = head = new_node;
			}
			else {
				tail->next = new_node;
				tail = new_node;
			}
			size++;
		}

		void PushBefore(std::shared_ptr<SLLNode<T>> Node, const T& value) {
			if (Node == head) {
				PushFront(value);
				return;
			}
			std::shared_ptr<SLLNode<T>> start = head;
			while (start->next != Node)
			{
				start = start->next;
				if (!start) {
					break;
				}
			}
			if (start->next == Node) {
				std::shared_ptr<SLLNode<T>> new_node(new SLLNode<T>());
				new_node->value = value;
				new_node->next = start->next;
				start->next = new_node;
				size++;
				return;
			}
			throw std::out_of_range("Node not in linked list");
		}

		T PopFront() {
			std::shared_ptr<SLLNode<T>> Node = head;
			if (head == tail) {
				head = tail = nullptr;
				size = 0;
				return Node->value;
			}
			head = head->next;
			size -= 1;
			return Node->value;
		}

		T PopAfter(std::shared_ptr<SLLNode<T>> Node) {
			std::shared_ptr<SLLNode<T>> nNode = Node->next;
			if (Node == tail) {
				throw std::out_of_range("End of Linked List Cant Remove");
			}
			if (nNode == tail) {
				Node->next = nullptr;
				tail = Node;
				size -= 1;
				return nNode->value;
			}
			std::shared_ptr<SLLNode<T>> nnNode = Node->next->next;
			Node->next = nnNode;
			size -= 1;
			return nNode->value;
		}

		T PopBack() {
			std::shared_ptr<SLLNode<T>> Node = head;
			if (head == tail) {
				head = tail = nullptr;
				size = 0;
				return Node->value;
			}

			while (Node->next != tail) {
				Node = Node->next;
			}

			std::shared_ptr<SLLNode<T>> pNode = Node->next;
			Node->next = nullptr;
			tail = Node;
			size -= 1;
			return pNode->value;
		}

		T PopBefore(std::shared_ptr<SLLNode<T>> Node) {
			if (Node == head) {
				throw std::out_of_range("Cant Remove Before Head");
			}

			if (head->next == Node) {
				return PopFront();
			}

			std::shared_ptr<SLLNode<T>> ppNode = head;
			while (ppNode->next->next != Node) {
				ppNode = ppNode->next;
			}

			std::shared_ptr<SLLNode<T>> pNode = ppNode->next;
			ppNode->next = ppNode->next->next;

			size -= 1;
			return pNode->value;
		}

		T Pop(std::shared_ptr<SLLNode<T>> Node) {
			if (Node == tail) return PopFront();
			if (Node == head) return PopBack();
			return PopBefore(Node->next);
		}

		std::shared_ptr<SLLNode<T>> GetNodeAt(int n) {
			if (n < 0 || n >= size) {
				return nullptr;
			}

			std::shared_ptr<SLLNode<T>> Node = head;
			for (int i = 0; i < n; i++) {
				Node = Node->next;
			}
			return Node;
		}

		std::shared_ptr<SLLNode<T>> operator[](int n) {
			return GetNodeAt(n);
		}

		std::shared_ptr<SLLNode<T>> find(const T& Val) {
			std::shared_ptr<SLLNode<T>> Node = head;
			while (Node) {
				if (Node->value == Val) {
					return Node;
				}
				Node = Node->next;
			}
			return nullptr;
		}

		template <typename T2>
		std::shared_ptr<SLLNode<T>> findBy(const T2& Val) {
			std::shared_ptr<SLLNode<T>> Node = head;
			while (Node) {
				if (Node->value == Val) {
					return Node;
				}
				Node = Node->next;
			}
			return nullptr;
		}

		bool Empty() {
			return size == 0;
		}

		int Size() {
			return size;
		}

		std::shared_ptr<SLLNode<T>> Head() {
			return head;
		}

		std::shared_ptr<SLLNode<T>> Tail() {
			return tail;
		}
	};
}