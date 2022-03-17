build:
	g++ -g -g tests main.cpp
test: build
	valgrind --leak-check ./tests