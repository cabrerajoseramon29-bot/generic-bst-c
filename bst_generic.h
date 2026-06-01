#ifndef BST_GENERIC_H
#define BST_GENERIC_H

#include <stddef.h>

typedef struct BSTNode BSTNode;

/**
 * Function pointer type for comparing two generic elements.
 * Should return:
 * < 0 if a is less than b
 * == 0 if a equals b
 * > 0 if a is greater than b
 */
typedef int (*CompareFunc)(const void *a, const void *b);

/* ================= OPERATIONS ================= */

/* Recursive generic insertion using a comparison callback */
BSTNode *bst_insert(BSTNode *root, void *elem, CompareFunc cmp);

/* Iterative generic search variant - O(1) Auxiliary Space Complexity */
BSTNode *bst_search(BSTNode *root, const void *target, CompareFunc cmp);

/* Generic node removal operation based on CLRS algorithms */
BSTNode *bst_remove(BSTNode *root, const void *target, CompareFunc cmp);

/* ================= TRAVERSALS & LIFECYCLE ================= */

/* In-order traversal that executes a custom action callback on each element */
void bst_inorder(BSTNode *root, void (*action)(void *));

/* Post-order traversal to clear all memory from the tree and its elements */
void bst_destroy(BSTNode *root, void (*free_elem)(void *));

#endif /* BST_GENERIC_H */