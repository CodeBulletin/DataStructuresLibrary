#pragma once
#include <string>
#include "../Stack.hpp"
#include <random>

bool isBalanced(const std::string& str) {

	DS::Stack<char> Stack;

	for (char i : str) {
		if (i == '{' || i == '(' || i == '[' || i == '<') Stack.Push(i);
		else if (i == '}' || i == ')' || i == ']' || i == '>')
		{
			if (Stack.Empty()) return false;
			char top = Stack.Pop(); 
			if ((top == '[' and i != ']') || (top == '(' and i != ')') ||
				(top == '{' and i != '}') || (top == '<' and i != '>'))
				return false;
		}
	}

	return Stack.Empty();
}

std::string makeBalancedString(int size) {

	static std::random_device rd;
	static std::mt19937 mt(rd());
	static std::uniform_int_distribution<int> dist(0, 3);

	if (size % 2 == 1) --size;
	std::string BalancedString = "";
	DS::Stack<int> Stack;

	char bracket_str[5] = "<[{(";
	char bracket_str_c[5] = ">]})";
	int i = 0;
	int ch = 0;

	while (i < size) {
		if (size - i > Stack.Size()) {
			if (dist(mt) % 2 == 0 || Stack.Size() == 0) {
				int ch = dist(mt);
				BalancedString += bracket_str[ch];
				Stack.Push(ch);
				i++;
			}
			else {
				BalancedString += bracket_str_c[Stack.Pop()];
				i++;
			}
		}
		else {
			BalancedString += bracket_str_c[Stack.Pop()];
			i++;
		}
	}
	return BalancedString;
}