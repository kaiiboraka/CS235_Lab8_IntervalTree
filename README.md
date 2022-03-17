# Lab Specification
*Interval Trees*

## Starting materials
- You are given `IntervalTree.h`. You should not modify this file.
    - `IntervalTree.h` contains the base class `IntervalTree`, which you will inherit.

## Intervals
- And interval has a lower and upper bound
    - For the purposes of our lab, the lower bound is **inclusive**, and the upper bound is **exclusive**
- Logic defining the qualities of intervals can be found in the `Interval` struct in `IntervalTree.h`

## Augmented Interval Tree
An *Augmented Interval Tree* (AIT) is a specialized Binary Search Tree (BST) that stores intervals instead of single values.
- Each AIT node also stores a "min-max" interval that defines the minimum lower bound and maximum upper bound of the local subtree.
    - See `Node` in `IntervalTree.h`

## Requirements
1. Create a class called `AugmentedIntervalTree` that inherits from `IntervalTree` (found in `IntervalTree.h`)
    1. Your class should be stored in `AugmentedIntervalTree.h`
        1. You do not need to separate your code into separate `.h` and `.cpp` files, though you may choose to do so if you desire.
        2. If you do write an `AugmentedIntervalTree.cpp`, be sure to submit it in addition to the other files.
        1. Note: it can be tricky to implement templated classes in a `.cpp`, so only attempt this if you know the issues and their solutions.
    2. This class must implement all the pure virtual functions found in `IntervalTree.h`
    3. This class is expected to not have any memory leaks
2. Write your own `tests.cpp`
    1. This file should contain a `int main() {...}` method that runs your tests
    2. You should include tests that exercise all the methods overridden in `AugmentedIntervalTree`
        1. You do not need to test large datasets, but you should try to verify that your code works properly
3. Write a `makefile`
    1. Target `test` should build a clean copy of your test binary and run your tests with valgrind
        1. **IMPORTANT** Do **not** include the `-s` flag for valgrind. See example makefile below.
4. Submit `AugmentedIntervalTree.h`, `tests.cpp`, and `makefile`

### Example `makefile`

*Be sure to use tabs and not spaces for indentation!*

```makefile
build:
    g++ -g -std=c++11 -o test tests.cpp

test: build
    valgrind --leak-check=full ./test
```

## How to get started

- Download the lab files
- Create a file named `AugmentedIntervalTree.h`
    - `AugmentedIntervalTree` should extend `IntervalTree`
- Stub out implementations of the inherited virtual methods
    - Simple `cout` statements and dummy return values
- Create a file named `my_tests.cpp`
    - Start with a simple `main` method that creates an `AugmentedIntervalTree`
- Create a `makefile` that looks like the example above
- **Make sure your code compiles before moving on!**
    - `make test` should run without errors
- For each of the following methods: `~AugmentedIntervalTree`, `is_empty`, `add`, `clear`, `query`, `remove`
    - Write tests that exercise that method and assert the state of the tree after the method is called
        - The new tests should fail
    - Implement the method
        - The tests should now pass
    - Once the last feature is well tested, move to the next feature
        - Keep the old tests: they will help you catch errors you introduce while implementing later features
- Things to test (not an exhaustive list):
    - Adding duplicate intervals
    - Remove intervals that aren't present
    - Add after clear
    - Query on empty
    - Query on boundaries (inclusive vs exclusive)
    - Remove on an empty tree
    - Query after remove
    - Structure after add and remove
    - Empty after clear?
- Other things to remember:
    - Make sure `query` uses an **inoder** traversal so the output is sorted
    - No memory leaks
    - To refer to `root` in your child class, use `this->root`. Do NOT override `root`, or this will cause the `to_string` method in the parent class to return the empty string.
- Turn in `AugmentedIntervalTree.h`, `my_tests.cpp`, and `makefile`

## Points

- 10 points for tests written by you
    - 2 points each for `is_empty`, `add`, `clear`, `query`, and `remove`
- 90 points for autograder tests
    - 20 points for basic tests of `add`, `clear` and `is_empty`
    - 20 points for basic tests of `add` and `query`
    - 20 points for basic tests of `add`, `query`, and `remove`
    - 10 points for advanced tests
    - 20 points for no memory leaks on all tests