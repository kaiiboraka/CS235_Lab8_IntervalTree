//
// Created by Gordon Bean on 2/23/22.
//

#ifndef LAB8_INTERVAL_TREE_INTERVALTREE_H
#define LAB8_INTERVAL_TREE_INTERVALTREE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<class T>
struct Interval
{
	T lower;
	T upper;

	Interval(T lower, T upper) : lower(lower), upper(upper)
	{}

	Interval(Interval<T> const& other) : lower(other.lower), upper(other.upper)
	{}

	bool operator==(Interval const& other) const
	{
		return this->lower == other.lower && this->upper == other.upper;
	}

	bool operator!=(Interval const& other) const
	{
		return !(*this == other);
	}

	bool operator<(Interval const& other) const
	{
		return this->lower < other.lower ||
			   (this->lower == other.lower && this->upper < other.upper);
	}

	bool contains(T const& point) const
	{
		return point >= lower && point < upper;
	}
};

/*
 * You will use this struct to build your interval tree
 */
template<class T>
struct Node
{
	Interval<T> interval;
	Interval<T> min_max;
	Node* left;
	Node* right;

	explicit Node(Interval<T> const& interval) : interval(interval), min_max(interval),
												 left(nullptr), right(nullptr)
	{}
};

template<class T>
class IntervalTree
{
protected:

	/*
	 * You'll need to delete this node and its children in your destructor
	 */
	Node<T>* root;

	/*
	 * You don't need to do anything with this method.
	 * It's a helper method for the public to_string method down below.
	 */
	string _to_string(Node<T>* const& node, int depth) const
	{
		stringstream ss;
		if (node->right != nullptr)
		{
			ss << _to_string(node->right, depth + 1);
		}
		for (int i = 0; i < depth; i++)
		{
			ss << "   ";
		}
		ss << node->interval;
		ss << "<" << node->min_max << ">" << endl;
		if (node->left != nullptr)
		{
			ss << _to_string(node->left, depth + 1);
		}
		return ss.str();
	}

public:
	IntervalTree() : root(nullptr)
	{}

	/*
	 * Normally, a base class should manage all of its variables,
	 * (i.e. delete root and its children)
	 * but one purpose of this project is to let you figure that part out,
	 * so, the child class should delete any relevant state.
	 */
	virtual ~IntervalTree() = default;

	/*
	 * Should delete all the intervals in the tree
	 */
	virtual void clear() = 0;

	/*
	 * Returns true if there are no intervals in the tree
	 */
	virtual bool is_empty() const = 0;

	/*
	 * Add an interval to the tree
	 * Make sure you update the min and max bounds on each node touched!
	 */
	virtual bool add(T const& lower, T const& upper) = 0;

	/*
	 * Query for ALL intervals that overlap the given point
	 * The output vector must be sorted
	 * Hint: perform the binary search using an inorder traversal
	 */
	virtual vector<Interval<T>> query(T const& point) const = 0;

	/*
	 * Remove the interval defined by the given lower and upper bounds
	 * Be sure to update the min and max bounds for each node touched!
	 */
	virtual bool remove(T const& lower, T const& upper) = 0;

	/*
	 * A handy method for visualizing the structure of the tree
	 * You don't need to override this, but you may find it useful
	 *   in writing tests and debugging
	 */
	string to_string() const
	{
		if (root == nullptr)
		{ return ""; }
		return _to_string(root, 0);
	}
};

//  **************************************************************************
//  The following functions may be useful for writing tests and debugging code
//  **************************************************************************


/*
 * A handy method for visualizing an Interval
 * e.g.
 * Interval<int> interval(7, 12);
 * cout << interval << endl;
 */
template<class T>
ostream& operator<<(ostream& stream, Interval<T> const& interval)
{
	return stream << "[" << interval.lower << ", " << interval.upper << ")";
}

/*
 * Handy method for visualizing an interval tree
 * e.g. cout << tree << endl;
 */
template<class T>
ostream& operator<<(ostream& stream, IntervalTree<T> const& tree)
{
	return stream << tree.to_string();
}

/*
 * Handy method for visualizing a vector of intervals
 * e.g.
 * vector<Interval<int>> intervals = tree.query(7);
 * cout << intervals << endl;
 */
template<class T>
ostream& operator<<(ostream& stream, vector<Interval<T>> const& intervals)
{
	return stream << to_string(intervals);
}

/*
 * Makes comparing two collections easier
 * Two collections are the same if they are the same size
 *   and all elements are the same.
 * For example, use this to compare the response of a query
 *   to the expected list of intervals.
 * i.e.
 * vector<Interval<int>> expected = {Interval<int>(1, 3), Interval<int>(2,4)};
 * vector<Interval<int>> observed = tree.query(2);
 * if (expected != observed) { throw "FAIL"; }
 */
template<class T>
bool operator==(T const& a, T const& b)
{
	if (a.size() != b.size())
	{
		return false;
	}
	auto ait = a.begin();
	auto bit = b.begin();
	while (ait != a.end() && bit != b.end())
	{
		if (*ait != *bit)
		{
			return false;
		}
		ait++;
		bit++;
	}
	return true;
}

template<class T>
bool operator!=(T const& a, T const& b)
{
	return !(a == b);
}

/*
 * Handy method for getting the contents of a collection in string form
 */
template<class T>
string to_string(T const& collection)
{
	stringstream stream;
	for (auto item : collection)
	{
		stream << item << " ";
	}
	return stream.str();
}

/*
 * Handy method for writing tests
 */
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

#endif //LAB8_INTERVAL_TREE_INTERVALTREE_H