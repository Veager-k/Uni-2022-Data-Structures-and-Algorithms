main:
	gcc -c binaryTree.c
	gcc -c treeTest.c
	ar cr libBinaryTree.a binaryTree.o
	gcc treeTest.o libBinaryTree.a -o treeTest.exe
	.\treeTest.exe