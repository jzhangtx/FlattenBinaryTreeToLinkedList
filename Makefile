FlatternBinaryTree: FlatternBinaryTree.o
	g++ -g -o FlatternBinaryTree.exe FlatternBinaryTree.o -pthread    

FlatternBinaryTree.o: FlatternBinaryTree/FlatternBinaryTree.cpp
	g++ -g  -c -pthread FlatternBinaryTree/FlatternBinaryTree.cpp
