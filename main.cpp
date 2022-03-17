#include "Tree.h"

int main()
{
	Tree<int> tree;

    test("is empty", tree.is_empty(), true);
    test("height", tree.height(), -1);
    test("add 7", tree.add(7), true);
    test("height", tree.height(), 0);
    test("add 7 dup", tree.add(7), false);
    test("height", tree.height(), 0);
    test("add 8", tree.add(8), true);
    test("height", tree.height(), 1);
    test("add 5", tree.add(5), true);
    test("height", tree.height(), 1);
    test("add 3", tree.add(3), true);
    test("height", tree.height(), 2);
	
    auto items = tree.query(9);
    test("query count",(int) items.size(), 2);
	
    vector<int> expected = {7, 8};
    for (int i = 0; i < items.size(); i++)
	{
        test("query item", items[i], expected[i]);
    }
	
    test("remove 3", tree.remove(3), true);
    test("remove 3 again", tree.remove(3), false);
    test("height", tree.height(), 1);
    test("remove 7", tree.remove(7), true);
    test("height", tree.height(), 1);
    test("remove 5", tree.remove(5), true);
    test("height", tree.height(), 0);
    test("remove 8", tree.remove(8), true);
    test("height", tree.height(), -1);
    return 0;

}