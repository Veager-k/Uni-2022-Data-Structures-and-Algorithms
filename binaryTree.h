// author_stud_id: 2110583

#ifndef binaryTree_H
#define binaryTree_H

typedef struct treeNode{
    int value;
    int balance;
    struct treeNode* left;
    struct treeNode* right;
} node;

typedef struct{
    node* root;
} BSTree;

void initializeTree(BSTree *tree);
void insertValueTree(BSTree *tree, int value, int *error);
void deleteValueTree(BSTree *tree, int value, int *error);
int doesValueExistBST(BSTree tree, int value);
void deleteTree(BSTree *tree);

// error codes
// 01 - failed to allocate memory when creating new node
// 02 - failed to add value as it already exists
// 03 - couldnt find node to delete
//

#endif