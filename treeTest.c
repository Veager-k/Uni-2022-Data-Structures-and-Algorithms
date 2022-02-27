#include <stdio.h>
#include "binaryTree.h"

void printTree(node *node);

int main(){

    BSTree tree;
    initializeTree(&tree);

    int error = 0;
    insertValueTree(&tree, 50, &error);
    insertValueTree(&tree, 30, &error);
    insertValueTree(&tree, 60, &error);
    insertValueTree(&tree, 70, &error);
    insertValueTree(&tree, 55, &error);

    printTree(tree.root);
    printf("------------------------\n");
    
    deleteValueTree(&tree, 60, &error);
    printTree(tree.root);
    printf("------------------------\n");
    
    printf("does x exist: %d\n", doesValueExistBST(tree, 55));

    deleteTree(&tree);
    printf("tree destroyed\n");
}

void printTree(node *node){
    printf("%d - %d\n", node->value, node->balance);

    if(node->left != NULL){
        printTree(node->left);
    }
    if(node->right != NULL){
        printTree(node->right);
    }
}