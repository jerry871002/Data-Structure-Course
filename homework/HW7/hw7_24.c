#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

typedef struct {
    int num;
    bool isThread;
} DATA;

int compare(DATA* data1, DATA* data2);
NODE* createThreaded(NODE *root);
NODE* leftMost(NODE *root);
void inOrder(NODE* root);

int main(int argc, char const *argv[]) {
    BST_TREE* tree = BST_Create(&compare);

    printf("Please enter a sequence of number(end by entering -1)\n");
    while(1) {
        DATA* data = (DATA*)malloc(sizeof(DATA));
        data->isThread = false;
        scanf("%d", &(data->num));

        if(data->num < 0) {
            free(data);
            break;
        }

        BST_Insert(tree, data);
    }

    createThreaded(tree->root);
    inOrder(tree->root);

    return 0;
}

int compare(DATA* data1, DATA* data2) {
    return data1->num - data2->num;
}

NODE* createThreaded(NODE *root) {
    // Base cases: Tree is empty or node is leaf
    if (root == NULL)
        return NULL;
    if (root->left == NULL && root->right == NULL)
        return root;

    // Find predecessor if it exists
    if (root->left != NULL) {
        // Find predecessor of root (Rightmost child in left subtree)
        NODE* pre = createThreaded(root->left);

        // Link a thread from predecessor to root.
        pre->right = root;
        ((DATA*)(pre->dataPtr))->isThread = true;
    }

    // If current node is rightmost child
    if (root->right == NULL)
        return root;

    // Recursive for right subtree.
    return createThreaded(root->right);
}

NODE* leftMost(NODE *root)  {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

void inOrder(NODE* root) {
    if (root == NULL)
        return;

    // Find the leftmost node in Binary Tree
    NODE* current = leftMost(root);

    while(current != NULL) {
        printf("%d ", ((DATA*)(current->dataPtr))->num);

        // If this Node is a thread Node, then go to inorder successor
        if (((DATA*)(current->dataPtr))->isThread)
            current = current->right;
        else // Else go to the leftmost child in right subtree
            current = leftMost(current->right);
    }
    printf("\n");
}
