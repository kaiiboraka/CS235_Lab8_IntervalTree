#pragma once

#include <string>
#include <iostream>
//#include "IntervalTree.h"
using namespace std;

template<class T>
struct Node
{
	T value;
	int height;
	Node* left;
	Node* right;

	explicit Node(T value) : value(value), height(0), left(nullptr), right(nullptr){}
};

template<class T>
class TreeBase
{
public:
	//TODO:
	TreeBase() : root(nullptr) {}
	~TreeBase() = default;

protected:
	Node<T>* root;

	virtual void clear() = 0;

	virtual bool is_empty() const = 0;

	virtual bool add(T item) = 0;

	virtual bool remove(T item) = 0;

};

template<class T>
void test(string const& message, T const& observed, T const& expected)
{
	cout << message << endl;
	cout << "Expected:" << endl << expected << "Observed:" << endl << observed << endl;
	if (expected == observed)
	{
		cout << "Passed ✅" << endl;
	}
	else
	{
		cerr << "Failed" << endl;
		throw invalid_argument(((string) "FAILED TEST: ") + message);
	}
}