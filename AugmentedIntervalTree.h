#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "IntervalTree.h"

template<class T>
class AugmentedIntervalTree : public IntervalTree<T>
{
	void ClearRecursion(Node<T>*& node)
	{
		if (node == nullptr)
		{
			return;
		}
		ClearRecursion(node->left);
		ClearRecursion(node->right);
		delete node;
		node = nullptr;
	}

	void UpdateMinMax(Node<T>*& currentNode)
	{
		if ( currentNode == nullptr)
		{
			return;
		}
		currentNode->min_max = currentNode->interval;

		if(currentNode->left != nullptr)
		{
			currentNode->min_max.lower = min(currentNode->min_max.lower, currentNode->left->min_max.lower);
			currentNode->min_max.upper = max(currentNode->min_max.upper, currentNode->left->min_max.upper);
		}
		if(currentNode->right != nullptr)
		{
			currentNode->min_max.lower = min(currentNode->min_max.lower, currentNode->right->min_max.lower);
			currentNode->min_max.upper = max(currentNode->min_max.upper, currentNode->right->min_max.upper);
		}
		return;
	}

	bool AddRecursion(Node<T>*& node, Interval<T> interval)
	{
		if (node == nullptr)
		{
			//this is the place
			node = new Node<T>(interval);
			UpdateMinMax(node);
			return true;
		}
		if (node->interval == interval)
		{
			cerr << "Hey! ADDING {"<< interval <<"} BORKED" << endl;
			return false;
		}
		else if (interval < node->interval)
		{
			bool added = AddRecursion(node->left, interval);
			if (added)
			{
				UpdateMinMax(node);
			}
			return added;
		}
		else // interval > node->value
		{
			bool added = AddRecursion(node->right, interval);
			if (added)
			{
				UpdateMinMax(node);
			}
			return added;
		}
	}

	bool RemoveRecursion(Node<T>*& node, Interval<T> interval)
	{
		if (node == nullptr)
		{
			//dead end
			return false;
		}
		if (node->interval == interval)
		{
			// have no children
			// have one child
			if (node->left == nullptr)
			{
				auto temp = node;
				node = node->right;
				delete temp;
				UpdateMinMax(node);
				return true;
			}
			else if (node->right == nullptr)
			{
				auto temp = node;
				node = node->left;
				delete temp;
				UpdateMinMax(node);
				return true;
			}
			else
			{
				// have 2 children -> swap IOP value
				// IOP is rightmost child in left branch
				// replace node value with IOP value
				// delete IOP value from left tree

				const Node<T>* iop = GetIOPredecessor(node);
				node->interval = iop->interval;
				RemoveRecursion(node->left, node->interval);
				return true;
			}

		}
		else if (interval < node->interval)
		{
			bool removed = (RemoveRecursion(node->left, interval));
			if(removed)
			{
				UpdateMinMax(node);
			}
			return removed;
		}
		else // if interval > node->value
		{
			bool removed = (RemoveRecursion(node->right, interval));
			if(removed)
			{
				UpdateMinMax(node);
			}
			return removed;
		}
	}

	Node<T>* GetIOPredecessor(Node<T>* const& node)
	{
		// will only ever call this if node-> left is not null
		// so no need to check if it is
		Node<T>* temp = node->left;
		while (temp->right != nullptr)
		{
			temp = temp->right;
		}
		return temp;
	}

	void QueryRecursion(Node<T>* node, T const& point, vector<Interval<T>>& items_found) const
	{
		if (node == nullptr)
		{
			return;
		}
		QueryRecursion(node->left, point, items_found);
		if (node->interval.contains(point))
		{
			items_found.push_back(node->interval);
		}
		QueryRecursion(node->right, point, items_found);
	}

public:
	AugmentedIntervalTree()
	{}

	~AugmentedIntervalTree()
	{
		clear();
	}

	void clear() override
	{
		ClearRecursion(this->root);
	}

	bool is_empty() const override
	{
		return (this->root == nullptr);
	}

	bool add(T const& lower, T const& upper) override
	{
		Interval<T> interval(lower, upper);
		return (AddRecursion(this->root, interval));
	}

	bool remove(T const& lower, T const& upper) override
	{
		Interval<T> interval(lower, upper);
		bool removed = (RemoveRecursion(this->root, interval));
		if(removed)
		{
			cerr << "Hey! REMOVING {"<< interval <<"} BORKED" << endl;
		}
		return removed;
	}

	vector<Interval<T>> query(T const& point) const override
	{
		vector<Interval<T>> nodes;
		QueryRecursion(this->root, point, nodes);
		return nodes;
	}

};