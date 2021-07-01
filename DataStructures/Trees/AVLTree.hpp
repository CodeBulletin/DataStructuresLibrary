#pragma once
#include "../Nodes.hpp"
#include "../Array.hpp"
#include "../Queue.hpp"
#include <functional>

namespace DS {
	template<typename T>
	class AVLTree {
	public:

		static const int inOrderSort = 0;
		static const int preOrderSort = 1;
		static const int postOrderSort = 2;
		static const int levelOrderSort = 3;

	private:
		std::shared_ptr<AVLNode<T>> Root;
		int size;

		DynamicArray<std::shared_ptr<AVLNode<T>>> List;

	public:
		AVLTree() {}
		AVLTree(const T& RootValue) {
			Root = std::make_shared<AVLNode<T>>(AVLNode<T>());
			Root->value = RootValue;
		}
		AVLTree(const AVLTree& BST) {
			size = BST.size;
			LevelOrderTraversal(BST.Root, [&](T& val) -> void { Insert(val); });
		}
		~AVLTree() {
			DeleteTree(Root);
		}

		void DeleteTree(std::shared_ptr<AVLNode<T>> node) {
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
			std::shared_ptr<AVLNode<T>> next = Root;
			if (!next) {
				Root = std::make_shared<AVLNode<T>>(AVLNode<T>());
				Root->value = Value;
				size++;
				return;
			}
			while (true) {
				if (Value < next->value) {
					if (!next->Left) {
						next->Left = std::make_shared<AVLNode<T>>(AVLNode<T>());
						next->Left->value = Value;
						next->Left->Parent = next;
						Rebalance(next->Left);
						break;
					}
					next = next->Left;
				}
				else {
					if (!next->Right) {
						next->Right = std::make_shared<AVLNode<T>>(AVLNode<T>());
						next->Right->value = Value;
						next->Right->Parent = next;
						Rebalance(next->Right);
						break;
					}
					next = next->Right;
				}
			}
			size++;
		}

		std::shared_ptr<AVLNode<T>> LeftRotate(std::shared_ptr<AVLNode<T>> X) {
			std::shared_ptr<AVLNode<T>> Y = X->Right;
			std::shared_ptr<AVLNode<T>> P = X->Parent;
			std::shared_ptr<AVLNode<T>> T2 = Y->Left;

			Y->Left = X;
			X->Right = T2;
			X->Parent = Y;
			Y->Parent = P;
			if (T2) {
				T2->Parent = X;
			}

			X->Height = std::max<int>(Height(X->Left), Height(X->Right)) + 1;
			Y->Height = std::max<int>(Height(Y->Left), Height(Y->Right)) + 1;

			return Y;
		}

		std::shared_ptr<AVLNode<T>> RightRotate(std::shared_ptr<AVLNode<T>> Y) {
			std::shared_ptr<AVLNode<T>> X = Y->Left;
			std::shared_ptr<AVLNode<T>> P = Y->Parent;
			std::shared_ptr<AVLNode<T>> T2 = X->Right;

			X->Right = Y;
			Y->Left = T2;
			Y->Parent = X;
			X->Parent = P;
			if (T2) {
				T2->Parent = Y;
			}

			Y->Height = std::max<int>(Height(Y->Left), Height(Y->Right)) + 1;
			X->Height = std::max<int>(Height(X->Left), Height(X->Right)) + 1;

			return X;
		}

		int Height(std::shared_ptr<AVLNode<T>> node) {
			if (!node) return 0;
			else return node->Height;
		}

		std::shared_ptr<AVLNode<T>> Find(const T& Value, std::shared_ptr<AVLNode<T>> node) {
			std::shared_ptr<AVLNode<T>> next = node;
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

		std::shared_ptr<AVLNode<T>> Find(const T& Value) {
			return Find(Value, Root);
		}

		std::shared_ptr<AVLNode<T>> Next(std::shared_ptr<AVLNode<T>> node) {
			if (!node->Right) {
				std::shared_ptr<AVLNode<T>> next = node;
				while (true)
				{
					if (next == Root) return next;
					if (next->value < next->Parent->value) return next->Parent;
					next = next->Parent;
				}
			}
			else {
				std::shared_ptr<AVLNode<T>> next = node->Right;
				while (true) {
					if (!next->Left) return next;
					next = next->Left;
				}
			}
		}

		std::shared_ptr<AVLNode<T>> Prev(std::shared_ptr<AVLNode<T>> node) {
			if (!node->Left) {
				std::shared_ptr<AVLNode<T>> next = node;
				while (true)
				{
					if (next == Root) return next;
					if (next->value >= next->Parent->value) return next->Parent;
					next = next->Parent;
				}
			}
			else {
				std::shared_ptr<AVLNode<T>> next = node->Left;
				while (true) {
					if (!next->Right) return next;
					next = next->Right;
				}
			}
		}

		std::shared_ptr<AVLNode<T>> Next(const T& Value) {
			return Next(Find(Value));
		}

		std::shared_ptr<AVLNode<T>> Prev(const T& Value) {
			return Prev(Find(Value));
		}

		DynamicArray<std::shared_ptr<AVLNode<T>>>& RangeSearch(const T& val1, const T& val2) {
			List.Clear();
			std::shared_ptr<AVLNode<T>> next = Find(val1);
			while (next->value <= val2) {
				if (next->value >= val1) {
					List.PushBack(next);
				}
				next = Next(next);
			}
			return List;
		}

		DynamicArray<std::shared_ptr<AVLNode<T>>>& Neighbours(const T& val) {
			List.Clear();
			List.PushBack(Prev(val));
			List.PushBack(Next(val));
			return List;
		}

		DynamicArray<std::shared_ptr<AVLNode<T>>>& Neighbours(std::shared_ptr<AVLNode<T>> node) {
			List.Clear();
			List.PushBack(Prev(node));
			List.PushBack(Next(node));
			return List;
		}

		T Delete(std::shared_ptr<AVLNode<T>> node) {
			T value = node->value;
			size--;
			if (isLeaf(node)) {
				if (node->Parent) {
					if (node == node->Parent->Right) node->Parent->Right = nullptr;
					else node->Parent->Left = nullptr;
					Rebalance(node->Parent);
				}
				else {
					Root = nullptr;
				}
				return value;
			}
			std::shared_ptr<AVLNode<T>> next, P;
			if ((node != Root) || (node->Right)) {
				next = Next(node);
				P = next->Parent;
			}
			else {
				next = Prev(node);
				P = next->Parent;
			}
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
			Rebalance(P);
			return value;
		}

		void Rebalance(std::shared_ptr<AVLNode<T>> node) {
			while (true) {
				std::shared_ptr<AVLNode<T>> parent = node->Parent;
				if (Height(node->Left) > Height(node->Right) + 1) RebalanceRight(node);
				else if (Height(node->Right) > Height(node->Left) + 1) RebalanceLeft(node);
				node->Height = std::max<int>(Height(node->Left), Height(node->Right)) + 1;
				if (!parent) break;
				node = parent;
			}
		}

		void RebalanceRight(std::shared_ptr<AVLNode<T>> node) {
			std::shared_ptr<AVLNode<T>> P = node->Parent;
			std::shared_ptr<AVLNode<T>> X = node->Left;
			if (Height(X->Right) > Height(X->Left)) node->Left = LeftRotate(X);
			if (P) {
				if (X->value >= P->value) P->Right = RightRotate(node);
				else P->Left = RightRotate(node);
				return;
			}
			Root = RightRotate(node);
		}

		void RebalanceLeft(std::shared_ptr<AVLNode<T>> node) {
			std::shared_ptr<AVLNode<T>> P = node->Parent;
			std::shared_ptr<AVLNode<T>> X = node->Right;
			if (Height(X->Right) < Height(X->Left)) RightRotate(X);
			if (P) {
				if (X->value >= P->value) P->Right = LeftRotate(node);
				else P->Left = LeftRotate(node);
				return;
			}
			Root = LeftRotate(node);
		}

		bool isLeaf(std::shared_ptr<AVLNode<T>> node) {
			return !node->Left && !node->Right;
		}

		int Size() {
			return size;
		}

		bool Empty() {
			return !Root;
		}

		std::shared_ptr<AVLNode<T>> getRoot() {
			return Root;
		}

		std::shared_ptr<AVLNode<T>> Max() {
			std::shared_ptr<AVLNode<T>> next = Root;
			while (true) {
				if (!next->Right) return next;
				next = next->Right;
			}
		}

		std::shared_ptr<AVLNode<T>> Min() {
			std::shared_ptr<AVLNode<T>> next = Root;
			while (true) {
				if (!next->Left) return next;
				next = next->Left;
			}
		}

		DynamicArray<std::shared_ptr<AVLNode<T>>>& getSortedArray(const int& sortType = inOrderSort) {
			List.Clear();
			auto Function = [&](std::shared_ptr<AVLNode<T>> node) -> void {
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

		void InOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			if (!node) return;
			InOrderTraversal(node->Left, function);
			function(node);
			InOrderTraversal(node->Right, function);
		}

		void InOrderTraversal(std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			InOrderTraversal(Root, function);
		}

		void InOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			InOrderTraversal(node->Left, function);
			function(node->value);
			InOrderTraversal(node->Right, function);
		}

		void InOrderTraversal(std::function<void(T&)> function) {
			InOrderTraversal(Root, function);
		}

		void PreOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			if (!node) return;
			function(node);
			PreOrderTraversal(node->Left, function);
			PreOrderTraversal(node->Right, function);
		}

		void PreOrderTraversal(std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			PreOrderTraversal(Root, function);
		}

		void PreOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			function(node->value);
			PreOrderTraversal(node->Left, function);
			PreOrderTraversal(node->Right, function);
		}

		void PreOrderTraversal(std::function<void(T&)> function) {
			PreOrderTraversal(Root, function);
		}

		void PostOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			if (!node) return;
			PostOrderTraversal(node->Left, function);
			PostOrderTraversal(node->Right, function);
			function(node);
		}

		void PostOrderTraversal(std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			PostOrderTraversal(Root, function);
		}

		void PostOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			PostOrderTraversal(node->Left, function);
			PostOrderTraversal(node->Right, function);
			function(node->value);
		}

		void PostOrderTraversal(std::function<void(T&)> function) {
			PostOrderTraversal(Root, function);
		}

		void LevelOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			if (!node) return;
			Queue<std::shared_ptr<AVLNode<T>>> nodes;
			nodes.Enqueue(node);
			while (!nodes.Empty()) {
				node = nodes.Dequeue();
				function(node);
				if (node->Left) nodes.Enqueue(node->Left);
				if (node->Right) nodes.Enqueue(node->Right);
			}
		}

		void LevelOrderTraversal(std::function<void(std::shared_ptr<AVLNode<T>>)> function) {
			LevelOrderTraversal(Root, function);
		}

		void LevelOrderTraversal(std::shared_ptr<AVLNode<T>> node, std::function<void(T&)> function) {
			if (!node) return;
			Queue<std::shared_ptr<AVLNode<T>>> nodes;
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
	};
}