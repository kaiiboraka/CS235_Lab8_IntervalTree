all:
	g++ -o tests tests.cpp -g
test: all
	valgrind --leak-check=full ./tests