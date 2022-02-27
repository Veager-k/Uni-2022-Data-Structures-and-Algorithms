#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

// add errors :D
void deleteTreeNodes(node *node);
void insert(node **root, int value, int* isTaller, int *error);
void rotateLeft(node **root);
void rotateRight(node **root);
void balanceRight(node **root);
void balanceLeft(node **root);
void deleteNode(node **root, int value, int* isDeleted, int *error);


void initializeTree(BSTree *tree){
    tree->root = 0;
}

void insertValueTree(BSTree *tree, int value, int *error){
    int temp = 0;
    insert(&(tree->root), value, &temp, error);
}

void insert(node **root, int value, int* isTaller, int *error){
    int isSubTreeTaller;
    if(*root == NULL){
        *root = (node *)malloc(sizeof(node));
        if(*root == NULL){
            *error = 1; //failed to allocate memory
            *isTaller = 0;
            return;
        }
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->balance = 0;
        *isTaller = 1;
        return;
    }
    else{
        if((*root)->value == value){
            *isTaller = 0;
            *error = 2; //value already exists
            return;
        }
        if((*root)->value > value){
            insert(&(*root)->left, value, &isSubTreeTaller, error);
            if(isSubTreeTaller){
                switch((*root)->balance){
                    case -1: //left heavy
                        balanceLeft(root);
                        *isTaller = 0;
                        return;
                    case 0: //balanced
                        (*root)->balance = -1;
                        *isTaller = 1;
                        return;
                    case 1: //right heavy
                        (*root)->balance = 0;
                        *isTaller = 0;
                        return;
                }
            }
            else{
                *isTaller = 0;
                return;
            }
        }
        else{
            insert(&(*root)->right, value, &isSubTreeTaller, error);
            if(isSubTreeTaller){
                switch((*root)->balance){
                    case -1:
                        (*root)->balance = 0;
                        *isTaller = 0;
                        return;
                    case 0:
                        (*root)->balance = 1;
                        *isTaller = 1;
                        return;
                    case 1:
                        balanceRight(root);
                        *isTaller = 0;
                        return;
                }
            }
            else{
                *isTaller = 0;
                return;
            }
        }
    }
}

void deleteValueTree(BSTree *tree, int value, int *error){
    int temp = 0;
    deleteNode(&(tree->root), value, &temp, error);
}

void deleteNode(node **root, int value, int* isDeleted, int *error){
    int wasSubTreeDeleted;
    if((*root)->value == value){
        if((*root)->left == NULL && (*root)->right == NULL){
            free(*root);
            *root = NULL;
            *isDeleted = 1;
            return;
        }

        else if((*root)->left != NULL && (*root)->right == NULL){
            node *tempNodePointer = (*root)->left;
            free(*root);
            (*root) = tempNodePointer;
            *isDeleted = 1;
            return;
        }

        else if((*root)->left == NULL && (*root)->right != NULL){
            node *tempNodePointer = (*root)->right;
            free((*root));
            (*root) = tempNodePointer;
            *isDeleted = 1;
            return;
        }

        else{
            node *minimumRightNode = (*root)->right;
            while(minimumRightNode->left != NULL){
                minimumRightNode = minimumRightNode->left;
            }
            int tempValue = (*root)->value;
            (*root)->value = minimumRightNode->value;
            minimumRightNode->value = tempValue;
            deleteNode(&(*root)->right, value, &wasSubTreeDeleted, error);
            if(wasSubTreeDeleted){
                switch((*root)->balance){
                    case -1: //left heavy
                        balanceLeft(root);
                        *isDeleted = 1;
                        return;
                    case 0:  //balanced
                        (*root)->balance = -1;
                        *isDeleted = 0;
                        return;
                    case 1: //right heavy
                        (*root)->balance = 0;
                        *isDeleted = 1;
                        return;
                }
            }
            else{
                *isDeleted = 0;
                return;
            }
        }
    }

    if((*root) == NULL){
        *isDeleted = 0;
        *error = 3;//couldnt find node to delete
        return;
    }
    if((*root)->value > value){
        deleteNode(&(*root)->left, value, &wasSubTreeDeleted, error);
        if(wasSubTreeDeleted){
            switch((*root)->balance){
                case -1: //left heavy;
                    (*root)->balance = 0;
                    *isDeleted = 1;
                    return;
                case 0: //balanced
                    (*root)->balance = 1;
                    *isDeleted = 0;
                    return;
                case 1: //right heavy
                    balanceRight(root);
                    *isDeleted = 1;
                    return;
            }
        }
        else{
            *isDeleted = 0;
            return;
        }
    }
    else{
        deleteNode(&(*root)->right, value, &wasSubTreeDeleted, error);
        if(wasSubTreeDeleted){
            switch((*root)->balance){
                case -1: //left heavy
                    balanceLeft(root);
                    *isDeleted = 1;
                    return;
                case 0:  //balanced
                    (*root)->balance = -1;
                    *isDeleted = 0;
                    return;
                case 1: //right heavy
                    (*root)->balance = 0;
                    *isDeleted = 1;
                    return;
            }
        }
        else{
            *isDeleted = 0;
            return;
        }
    }
}

void rotateLeft(node **root){
    node *temp;
    if(root == NULL){
        return;
    }
    else if((*root)->right == NULL){
        return;
    }
    else{
        temp = (*root)->right;
        (*root)->right = temp->left;
        temp->left = *root;
        *root = temp;
    }
}

void rotateRight(node **root){
    node *temp;
    if(*root == NULL){
        return;
    }

    temp = (*root)->left;
    (*root)->left = temp->right;
    temp->right = *root;
    *root = temp;
}

void balanceRight(node **root){
    node *rightChild = (*root)->right;
    node *leftChild;
    switch(rightChild->balance){
        case -1://left heavy
            leftChild = rightChild->left;
            switch(rightChild->balance){
                case -1:
                    (*root)->balance = 0;
                    rightChild->balance = 1;
                    break;
                case 0:
                    (*root)->balance = 0;
                    rightChild->balance = 0;
                    break;
                case 1:
                    (*root)->balance = -1;
                    rightChild->balance = 0;
                    break;
            }
            leftChild->balance = 0;
            rotateRight(&rightChild);
            (*root)->right = rightChild;
            rotateLeft(root);
            return;

        case 0://balanced
            (*root)->balance = 1;
            rightChild->balance = -1;
            rotateLeft(root);
            return;

        case 1://right heavy
            (*root)->balance = 0;
            rightChild->balance = 0;
            rotateLeft(root);
            return;
    }
}

void balanceLeft(node **root){
    node *leftChild = (*root)->left;
    node *rightChild;
    switch(leftChild->balance){
        case -1://left heavy
            (*root)->balance = 0;
            leftChild->balance = 0;
            rotateRight(root);
            return;

        case 0://balanced
            (*root)->balance = -1;
            leftChild->balance = 1;
            rotateRight(root);
            return;

        case 1://right heavy
            rightChild = leftChild->right;
            switch(rightChild->balance){
                case -1:
                    (*root)->balance = 1;
                    leftChild->balance = 0;
                    break;
                case 0:
                    (*root)->balance = 0;
                    leftChild->balance = 0;
                    break;
                case 1:
                    (*root)->balance = 0;
                    leftChild->balance = -1;
                    break;
            }
            rightChild->balance = 0;
            rotateLeft(&leftChild);
            (*root)->left = leftChild;
            rotateRight(root);
            return;
    }
}

int doesValueExistBST(BSTree tree, int value){
    node *currNode = tree.root;
    if(currNode == NULL){
        return 0;
    }

    while(currNode->value != value){
        if(currNode->value > value){
            currNode = currNode->left;
        }
        else{
            currNode = currNode->right;
        }

        if(currNode == NULL){
            return 0;
        }
    }

    return 1;
}

void deleteTree(BSTree *tree){
    deleteTreeNodes(tree->root);
    initializeTree(tree);
}

void deleteTreeNodes(node *node){
    if(node->left != NULL){
        deleteTreeNodes(node->left);
    }
    if(node->right != NULL){
        deleteTreeNodes(node->right);
    }
    free(node);
}
