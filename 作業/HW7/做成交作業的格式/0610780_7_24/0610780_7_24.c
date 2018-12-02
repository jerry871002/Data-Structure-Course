#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "0610780_7_24.h"

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
    if (root == NULL)
        return NULL;
    if (root->left == NULL && root->right == NULL)
        return root;

    if (root->left != NULL) {
        NODE* pre = createThreaded(root->left);

        pre->right = root;
        ((DATA*)(pre->dataPtr))->isThread = true;
    }

    if (root->right == NULL)
        return root;

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

    NODE* current = leftMost(root);

    while(current != NULL) {
        printf("%d ", ((DATA*)(current->dataPtr))->num);

        if (((DATA*)(current->dataPtr))->isThread)
            current = current->right;
        else
            current = leftMost(current->right);
    }
    printf("\n");
}
