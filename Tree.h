#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "TreeBase.h"

template<class T>
class Tree : public TreeBase<T>
{
	void _clear(Node<T>*& node)
	{
		if (node == nullptr)
		{
			return;
		}
		_clear(node->left);
		_clear(node->right);
		delete node;
	}

	bool _add(Node<T>*& node, T item)
	{
		if (node == nullptr)
		{
			//this is the place
			node = new Node<T>(item);
			return true;
		}

		if (node->value == item)
		{
			return false;
		}
		else if (item < node->value)
		{
			bool added = add(node->left, item);
			if (added)
			{
				_update_height(node);
			}
			return added;
		}
		else // item > node->value
		{
			bool added = add(node->right, item);
			if (added)
			{
				_update_height(node);
			}
			return added;
		}

	}

	bool _remove(Node<T>*& node, T item)
	{
		bool removed = false;
		if (node == nullptr)
		{
			removed = false;
		}

		if (node->value == item)
		{
			// have no children
			// have one child
			if (node->left == nullptr)
			{
				auto temp = node;
				node = node->right;
				delete temp;
				removed = true;
			}
			else if (node->right == nullptr)
			{
				auto temp = node;
				node = node->left;
				delete temp;
				removed = true;
			}
			else
			{
				// have 2 children -> swap IOP value
				//IOP is rightmost child in left branch
				// replace node value with IOP value
				// delete IOP value from left tree

				T const& iop_value = _get_iop_value(node);
				node->value = iop_value;
				_remove(node->left, iop_value);
				removed = true;
			}

		}
		else if (item < node->value)
		{
			removed = (_remove(node->left, item));
		}
		else // if item > node->value
		{
			removed = (_remove(node->right, item));
		}

		if (removed)
		{
			_update_height(node);
		}

		return removed;
	}

	T const& _get_iop_value(Node<T>* const& node)
	{
		// will only ever call this if node-> left is not null
		// so no need to check if it is
		auto temp = node->left;
		while (temp->right != nullptr)
		{
			temp = temp->right;
		}
		return temp->value;
	}

	void _update_height(Node<T>*& node)
	{
		if (node == nullptr){ return; }

		node->height = 1 + max
			(
				node->left == nullptr ? -1 : node->left->height,
				node->right == nullptr ? -1 : node->right->height
			);
	}

	vector<T> _query(const Node<T>*& node, const T& item, vector<T>& items_found)
	{
		if (node == nullptr)
		{
			return;
		}

		_query(node->left, item, items_found);


		//if (abs(node->value - item) <= 3)
		if (node->value + 3 <= item && node->value - 3 >= item)
		{
			items_found.push_back(node->value);
		}

		_query(node->right, item, items_found);

	}

public:
	Tree()
	{}

	~Tree()
	{
		clear();
	}

	int height() const
	{
		return (this->root == nullptr) ? -1 : this->root->height;
	}

	void clear() override
	{
		_clear(this->root)
	}

	bool is_empty() const override
	{
		return (this->root == nullptr);
	}

	bool add(T item) override
	{
		return (_add(this->root, item));
	}

	bool remove(T item) override
	{
		return (_remove(this->root, item));
	}

	vector<T> query(T item)
	{
		// return every value that is "close" to item
		// Define close: +/- 3 from item (inclusive)

	}

};