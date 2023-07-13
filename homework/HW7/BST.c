#include <stdbool.h>
#include <stdlib.h>
#include "BST.h"

BST_TREE* BST_Create(int (*compare)(void* argu1, void* argu2)) {
    BST_TREE* tree;

    tree = (BST_TREE*)malloc(sizeof(BST_TREE));
    if(tree) {
        tree->root = NULL;
        tree->count = 0;
        tree->compare = compare;
    }

    return tree;
}

BST_TREE* BST_Destroy(BST_TREE* tree) {
    if(tree)
        _destroy(tree->root);

    // All nodes deleted. Free structure
    free(tree);
    return NULL;
}

bool BST_Insert(BST_TREE* tree, void* dataPtr) {
    NODE* newPtr;

    newPtr = (NODE*)malloc(sizeof(NODE));
    if(!newPtr)
        return false;

    newPtr->right = NULL;
    newPtr->left = NULL;
    newPtr->dataPtr = dataPtr;

    if(tree->count == 0)
        tree->root = newPtr;
    else
        _insert(tree, tree->root, newPtr);

    (tree->count)++;
    return true;
}

bool BST_Delete(BST_TREE* tree, void* dltKey) {
    bool success;
    NODE* newRoot;

    newRoot = _delete(tree, tree->root, dltKey, &success);

    if(success) {
        tree->root = newRoot;
        (tree->count)--;
        if(tree->count == 0)
            tree->root = NULL;
    }
    return success;
}

void* BST_Retrieve(BST_TREE* tree, void* keyPtr) {
    if(tree->root)
        return _retreive(tree, keyPtr, tree->root);
    else
        return NULL;
}

void BST_Traverse(BST_TREE* tree, void (*process)(void* dataPtr)) {
    _traverse(tree->root, process);
    return;
}

bool BST_Empty(BST_TREE* tree) {
    return (tree->count == 0);
}

bool BST_Full(BST_TREE* tree) {
    NODE* newPtr;

    newPtr = (NODE*)malloc(sizeof(NODE));
    if(newPtr) {
        free(newPtr);
        return false;
    } else
        return true;
}

int BST_Count(BST_TREE* tree) {
    return (tree->count);
}

static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newPtr) {
    if(!root)
        return newPtr;

    if(tree->compare(newPtr->dataPtr, root->dataPtr) < 0) {
        root->left = _insert(tree, root->left, newPtr);
        return root;
    } else {
        root->right = _insert(tree, root->right, newPtr);
        return root;
    }
    return root;
}

static NODE* _delete(BST_TREE* tree, NODE* root, void* dataPtr, bool* success) {
    NODE* dltPtr;
    NODE* exchPtr;
    NODE* newRoot;

    if(!root) {
        *success = false;
        return NULL;
    }

    if(tree->compare(dataPtr, root->dataPtr) < 0)
        root->left = _delete(tree, root->left, dataPtr, success);
    else if(tree->compare(dataPtr, root->dataPtr) > 0)
        root->right = _delete(tree, root->right, dataPtr, success);
    else { // Delete node found, test for leaf node
        dltPtr = root;
        if(!root->left) { // No left subtree
            free(root->dataPtr);
            newRoot = root->right;
            free(dltPtr);
            *success = true;
            return newRoot;
        } else {
            if(!root->right) { // Only left subtree
                free(root->dataPtr);
                newRoot = root->left;
                free(dltPtr);
                *success = true;
                return newRoot;
            } else { // Delete Node has two subtrees
                exchPtr = root->left;
                // Find largest node on left subtree
                while(exchPtr->right)
                    exchPtr = exchPtr->right;

                root->dataPtr = exchPtr->dataPtr;
                root->left = _delete(tree, root->left, exchPtr->dataPtr, success);
            }
        }
    }
    return root;
}

static void* _retreive(BST_TREE* tree, void* dataPtr, NODE* root) {
    if(root) {
        if(tree->compare(dataPtr, root->dataPtr) < 0)
            return _retreive(tree, dataPtr, root->left);
        else if(tree->compare(dataPtr, root->dataPtr) > 0)
            return _retreive(tree, dataPtr, root->right);
        else
            // Found equal key
            return root->dataPtr;
    } else
        // Data not in tree
        return NULL;
}

static void _traverse(NODE* root, void (*process)(void* dataPtr)) {
    if(root) {
        _traverse(root->left, process);
        process(root->dataPtr);
        _traverse(root->right, process);
    }
    return;
}

static void _destroy(NODE* root) {
    if(root) {
        _destroy(root->left);        
        _destroy(root->right);
        free(root->dataPtr);
        free(root);
    }
    return;
}
