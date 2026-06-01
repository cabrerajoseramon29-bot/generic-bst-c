#include <stdio.h>
#include <stdlib.h>
#include "bst_generic.h"

struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
};

/* ================= LIFECYCLE ================= */

/* Internal helper function to allocate and initialize a new generic node */
static BSTNode *node_create(void *elem) {
    BSTNode *new_node = malloc(sizeof(BSTNode));
    if (!new_node) return NULL;

    new_node->data = elem;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/* Post-order traversal to safely clear all memory from the tree and its elements */
void bst_destroy(BSTNode *root, void (*free_elem)(void *)) {
    if (!root)
        return;

    bst_destroy(root->left, free_elem);
    bst_destroy(root->right, free_elem);

    if (free_elem)
        free_elem(root->data);

    free(root);
}

/* ================= OPERATIONS ================= */

/* Recursive generic insertion using a comparison callback */
BSTNode *bst_insert(BSTNode *root, void *elem, CompareFunc cmp) {
    /* Base Case: If the sub-tree is empty, hang the new node here */
    if (!root) {
        return node_create(elem);
    }

    int res = cmp(elem, root->data);

    if (res < 0) {
        root->left = bst_insert(root->left, elem, cmp);
    } else if (res > 0) {
        root->right = bst_insert(root->right, elem, cmp);
    }
    
    return root;
}

/* Iterative generic search variant - O(1) Auxiliary Space Complexity */
BSTNode *bst_search(BSTNode *root, const void *target, CompareFunc cmp) {
    if (!cmp) return NULL;

    while (root) {
        int res = cmp(target, root->data);

        if (res == 0) {
            return root; /* Target element located */
        }
        
        if (res > 0) {
            root = root->right; /* Target is larger, jump right */
        } else {
            root = root->left;  /* Target is smaller, jump left */
        }
    }
    
    return NULL;
}

/* Generic node removal operation based on CLRS algorithms */
BSTNode *bst_remove(BSTNode *root, const void *target, CompareFunc cmp) {
    if (!root) return NULL;

    int res = cmp(target, root->data);

    if (res > 0) {
        root->right = bst_remove(root->right, target, cmp);
    } else if (res < 0) {
        root->left = bst_remove(root->left, target, cmp);
    }
    /* Target node found */
    else {
        /* CASE 1 & 2: Node with only one child or no children (leaf) */
        if (!root->left) {
            BSTNode *temp = root->right; /* Grandparent adopts the right child */
            free(root);
            return temp;
        } else if (!root->right) {
            BSTNode *temp = root->left;  /* Grandparent adopts the left child */
            free(root);
            return temp;
        }
        
        /* CASE 3: Node with two children */
        /* Find the in-order successor (one step right, then all the way left) */
        BSTNode *successor = root->right;
        while (successor->left) {
            successor = successor->left;
        }
        
        /* Swap the generic element pointer to the current node */
        root->data = successor->data;

        /* Recursively extract the duplicate successor node from the right sub-tree */
        root->right = bst_remove(root->right, successor->data, cmp);
    }
    return root;
}