all:
	g++ -o tests tests.cpp -g
test: all
	valgrind --leak-check=full ./tests
autograder:
	g++ -o auto interval_tree_tests.cpp -g
	valgrind --leak-check=full ./auto