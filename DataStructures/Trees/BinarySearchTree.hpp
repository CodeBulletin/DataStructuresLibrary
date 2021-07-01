#pragma once
#include "../Nodes.hpp"
#include "../Array.hpp"
#include "../Queue.hpp"
#include <functional>

namespace DS {
	template<typename T>
	class BinarySearchTree {
	public:
		static const int inOrderSort = 0;
		static const int preOrderSort = 1;
		static const int postOrderSort = 2;
		static const int levelOrderSort = 3;

	private:
		std::shared_ptr<BSTNode<T>> Root;
		int size;

		DynamicArray<std::shared_ptr<BSTNode<T>>> List;

	public:
		BinarySearchTree() {}
		BinarySearchTree(const T& RootValue) {
			Root = std::make_shared<BSTNode<T>>(BSTNode<T>());
			Root->value = RootValue;
		}
		BinarySearchTree(const BinarySearchTree& BST) {
			size = BST.size;
			LevelOrderTraversal(BST.Root, [&](T& val) -> void { Insert(val); });
		}
		~BinarySearchTree() {
			DeleteTree(Root);
		}

		void DeleteTree(std::shared_ptr<BSTNode<T>> node) {
			if (!node) return;
			DeleteTree(node->Left);
			DeleteTree(node->Right);

			if (node == Root) {
				Root = nullptr;
				return;
			}
			if (node->Parent->value <= node->value) {
				node->Parent->Right.reset();
				node.reset();
				return;
			}
			else {
				node->Parent->Left.reset();
				node.reset();
				return;
			}
		}

		void Insert(const T& Value) {
			std::shared_ptr<BSTNode<T>> next = Root;
			if (!next) {
				Root = std::make_shared<BSTNode<T>>(BSTNode<T>());
				Root->value = Value;
				size++;
				return;
			}
			while (true) {
				if (Value < next->value) {
					if (!next->Left) {
						next->Left = std::make_shared<BSTNode<T>>(BSTNode<T>());
						next->Left->value = Value;
						next->Left->Parent = next;
						break;
					}
					next = next->Left;
				}
				else {
					if (!next->Right) {
						next->Right = std::make_shared<BSTNode<T>>(BSTNode<T>());
						next->Right->value = Value;
						next->Right->Parent = next;
						break;
					}
					next = next->Right;
				}
			}
			size++;
		}

		std::shared_ptr<BSTNode<T>> Find(const T& Value, std::shared_ptr<BSTNode<T>> node) {
			std::shared_ptr<BSTNode<T>> next = node;
			while (true) {
				if (next->value == Value) {
					return next;
				} 
				if (Value < next->value) {
					if (next->Left) next = next->Left;
					else return next;
				}
				else {
					if (next->Right) next = next->Right;
					else return next;
				}
			}
		}

		std::shared_ptr<BSTNode<T>> Find(const T& Value) {
			return Find(Value, Root);
		}

		std::shared_ptr<BSTNode<T>> Next(std::shared_ptr<BSTNode<T>> node) {
			if (!node->Right) {
				std::shared_ptr<BSTNode<T>> next = node;
				while (true)
				{
					if (next == Root) return next;
					if (next->value < next->Parent->value) return next->Parent;
					next = next->Parent;
				}
			}
			else {
				std::shared_ptr<BSTNode<T>> next = node->Right;
				while (true) {
					if (!next->Left) return next;
					next = next->Left;
				}
			}
		}

		std::shared_ptr<BSTNode<T>> Prev(std::shared_ptr<BSTNode<T>> node) {
			if (!node->Left) {
				std::shared_ptr<BSTNode<T>> next = node;
				while (true)
				{
					if (next == Root) return next;
					if (next->value >= next->Parent->value) return next->Parent;
					next = next->Parent;
				}
			}
			else {
				std::shared_ptr<BSTNode<T>> next = node->Left;
				while (true) {
					if (!next->Right) return next;
					next = next->Right;
				}
			}
		}

		std::shared_ptr<BSTNode<T>> Next(const T& Value) {
			return Next(Find(Value));
		}

		std::shared_ptr<BSTNode<T>> Prev(const T& Value) {
			return Prev(Find(Value));
		}

		DynamicArray<std::shared_ptr<BSTNode<T>>>& RangeSearch(const T& val1, const T& val2) {
			List.Clear();
			std::shared_ptr<BSTNode<T>> next = Find(val1);
			while (next->value <= val2) {
				if (next->value >= val1) {
					List.PushBack(next);
				}
				next = Next(next);
			}
			return List;
		}

		DynamicArray<std::shared_ptr<BSTNode<T>>>& Neighbours(const T& val) {
			List.Clear();
			List.PushBack(Prev(val));
			List.PushBack(Next(val));
			return List;
		}

		DynamicArray<std::shared_ptr<BSTNode<T>>>& Neighbours(std::shared_ptr<BSTNode<T>> node) {
			List.Clear();
			List.PushBack(Prev(node));
			List.PushBack(Next(node));
			return List;
		}

		T Delete(std::shared_ptr<BSTNode<T>> node) {
			T value = node->value;
			size--;
			if (isLeaf(node)) {
				if (node->Parent) {
					if (node == node->Parent->Right) node->Parent->Right = nullptr;
					else node->Parent->Left = nullptr;
				}
				else {
					Root = nullptr;
				}
				return value;
			}
			std::shared_ptr<BSTNode<T>> next;
			if ((node != Root) && (node->Right)) next = Next(node);
			else next = Prev(node);
			node->value = next->value;
			if (!isLeaf(next)) {
				if (next->Right) {
					next->Right->Parent = next->Parent;
					if (next == next->Parent->Right) next->Parent->Right = next->Right;
					else next->Parent->Left = next->Right;
				}
				else {
					next->Left->Parent = next->Parent;
					if (next == next->Parent->Right) next->Parent->Left = next->Left;
					else next->Parent->Left = next->Left;
				}
			}
			else {
				if (next == next->Parent->Right) next->Parent->Right = nullptr;
				else next->Parent->Left = nullptr;
			}
			return value;
		}

		bool isLeaf(std::shared_ptr<BSTNode<T>> node) {
			return !node->Left && !node->Right;
		}

		int Size() {
			return size;
		}

		bool Empty() {
			return !Root;
		}

		std::shared_ptr<BSTNode<T>> getRoot() {
			return Root;
		}

		DynamicArray<std::shared_ptr<BSTNode<T>>>& getSortedArray(const int& sortType = inOrderSort) {
			List.Clear();
			auto Function = [&](std::shared_ptr<BSTNode<T>> node) -> void {
				List.PushBack(node);
			};
			switch (sortType)
			{
			case inOrderSort:
				InOrderTraversal(Root, Function);
				break;
			case preOrderSort:
				PreOrderTraversal(Root, Function);
				break;
			case postOrderSort:
				PostOrderTraversal(Root, Function);
				break;
			case levelOrderSort:
				LevelOrderTraversal(Root, Function);
				break;
			default:
				InOrderTraversal(Root, Function);
				break;
			}
			return List;
		}

		void InOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			if (!node) return;
			InOrderTraversal(node->Left, function);
			function(node);
			InOrderTraversal(node->Right, function);
		}

		void InOrderTraversal(std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			InOrderTraversal(Root, function);
		}

		void InOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			InOrderTraversal(node->Left, function);
			function(node->value);
			InOrderTraversal(node->Right, function);
		}

		void InOrderTraversal(std::function<void(T&)> function) {
			InOrderTraversal(Root, function);
		}

		void PreOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			if (!node) return;
			function(node);
			PreOrderTraversal(node->Left, function);
			PreOrderTraversal(node->Right, function);
		}

		void PreOrderTraversal(std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			PreOrderTraversal(Root, function);
		}

		void PreOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			function(node->value);
			PreOrderTraversal(node->Left, function);
			PreOrderTraversal(node->Right, function);
		}

		void PreOrderTraversal(std::function<void(T&)> function) {
			PreOrderTraversal(Root, function);
		}

		void PostOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			if (!node) return;
			PostOrderTraversal(node->Left, function);
			PostOrderTraversal(node->Right, function);
			function(node);
		}

		void PostOrderTraversal(std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			PostOrderTraversal(Root, function);
		}

		void PostOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			PostOrderTraversal(node->Left, function);
			PostOrderTraversal(node->Right, function);
			function(node->value);
		}

		void PostOrderTraversal(std::function<void(T&)> function) {
			PostOrderTraversal(Root, function);
		}

		void LevelOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			if (!node) return;
			Queue<std::shared_ptr<BSTNode<T>>> nodes;
			nodes.Enqueue(node);
			while (!nodes.Empty()) {
				node = nodes.Dequeue();
				function(node);
				if (node->Left) nodes.Enqueue(node->Left);
				if (node->Right) nodes.Enqueue(node->Right);
			}
		}

		void LevelOrderTraversal(std::function<void(std::shared_ptr<BSTNode<T>>)> function) {
			LevelOrderTraversal(Root, function);
		}

		void LevelOrderTraversal(std::shared_ptr<BSTNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			Queue<std::shared_ptr<BSTNode<T>>> nodes;
			nodes.Enqueue(node);
			while (!nodes.Empty()) {
				node = nodes.Dequeue();
				function(node->value);
				if (node->Left) nodes.Enqueue(node->Left);
				if (node->Right) nodes.Enqueue(node->Right);
			}
		}
		
		void LevelOrderTraversal(std::function<void(T&)> function) {
			LevelOrderTraversal(Root, function);
		}

		std::shared_ptr<BSTNode<T>> Max() {
			std::shared_ptr<BSTNode<T>> next = Root;
			while (true) {
				if (!next->Right) return next;
				next = next->Right;
			}
		}

		std::shared_ptr<BSTNode<T>> Min() {
			std::shared_ptr<BSTNode<T>> next = Root;
			while (true) {
				if (!next->Left) return next;
				next = next->Left;
			}
		}
	};
}