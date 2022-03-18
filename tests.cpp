#include "AugmentedIntervalTree.h"

int main()
{
	AugmentedIntervalTree<int> tree;

	test("Empty Check", tree.is_empty(), true);
	test("remove fake [1, 9)", tree.remove(1, 9), false);

	auto query = tree.query(6);
	bool qFound = (query.size() > 0);
	test("Find 6", qFound, false);

	test("add [4, 6)", tree.add(4, 6), true);
	query = tree.query(6);
	qFound = (query.size() > 0);
	test("Find 6", qFound, false);
	test("Empty Check", tree.is_empty(), false);

	test("add [4, 6)", tree.add(4, 6), false);
	test("add [3, 5)", tree.add(3, 5), true);
	test("add [6, 8)", tree.add(6, 8), true);
	query = tree.query(6);
	qFound = (query.size() > 0);
	test("Find 6", qFound, true);

	test("add [1, 3)", tree.add(1, 3), true);
	test("add [7, 9)", tree.add(7, 9), true);
	test("remove [3, 5)", tree.remove(3, 5), true);
	test("remove fake [1, 9)", tree.remove(1, 9), false);

	tree.clear();
	test("clear", tree.is_empty(), true);

	return 0;
}