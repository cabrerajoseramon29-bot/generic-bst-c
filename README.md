# generic-bst-c
Generic Binary Search Tree implementation in C using function pointers for comparison and traversal callbacks.
# Generic BST in C

A generic Binary Search Tree (BST) implementation written in C.

This project demonstrates the implementation of a Binary Search Tree using
generic pointers (`void *`) and user-defined callbacks for comparison,
traversal actions, and memory management.

## Features

- Generic element storage using `void *`
- Recursive insertion
- Iterative search
- Node deletion
- In-order traversal
- Post-order destruction
- Custom comparison callbacks
- Custom cleanup callbacks
- Dynamic memory management

## Project Structure

```text
.
├── bst_generic.h
├── bst_generic.c
└── main.c
```

## API

### Insert

```c
BSTNode *bst_insert(
    BSTNode *root,
    void *elem,
    CompareFunc cmp
);
```

### Search

```c
BSTNode *bst_search(
    BSTNode *root,
    const void *target,
    CompareFunc cmp
);
```

### Remove

```c
BSTNode *bst_remove(
    BSTNode *root,
    const void *target,
    CompareFunc cmp
);
```

### In-order Traversal

```c
void bst_inorder(
    BSTNode *root,
    void (*action)(void *)
);
```

### Destroy

```c
void bst_destroy(
    BSTNode *root,
    void (*free_elem)(void *)
);
```

## Example

### Integer Comparison

```c
int int_cmp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
```

### Integer Print

```c
void print_int(void *data)
{
    printf("%d ", *(int *)data);
}
```

### Usage

```c
BSTNode *root = NULL;

root = bst_insert(root, value1, int_cmp);
root = bst_insert(root, value2, int_cmp);
root = bst_insert(root, value3, int_cmp);

bst_inorder(root, print_int);

bst_destroy(root, free);
```

## Complexity

| Operation | Average Case | Worst Case |
|------------|------------|------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Remove | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

## Notes

This implementation is intended for educational purposes and focuses on:

- Recursion
- Divide and Conquer
- Dynamic memory management
- Generic programming in C
- Fundamental tree algorithms

## References

- Introduction to Algorithms (CLRS)
- Binary Search Trees
- Data Structures and Algorithms in C

## License

MIT License
