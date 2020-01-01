#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

/*
 * heap methods
 */ 

// heap functions
void* maximum(void *, void*, int (*)(const void *, const void *));
void *left_child(void *, size_t, size_t, int);
void* right_child(void *, size_t, size_t, int);

void h_restore(void *, size_t, size_t, int, int (*)(const void *, const void *));
void h_init(void *, size_t, size_t, int (*)(const void *, const void *));

// get the maximum of 2 based on the comparator provided
void* maximum(void *a, void *b, int (*cmp)(const void *, const void *)){
    assert(a && b);
    return cmp(a, b) > 0 ? a : b;
}

// get the left child of a node in an array-represented heap, by node index
void* left_child(void *heap, size_t length, size_t size, int i){
    assert(heap);
    return (2 * i + 1 < length) ? heap + size * (2 * i + 1) : NULL;
}

// get the right child of a node in an array-represented heap, by node index
void* right_child(void *heap, size_t length, size_t size, int i){
    assert(heap);
    return (2 * (i + 1) < length) ? heap + size * (2 * (i + 1)) : NULL;
}

// restore the heap property in the sub-tree starting at $index
void h_restore(void *heap, size_t length, size_t size, int index, int (*cmp)(const void *, const void *)){
    int right_index, left_index;
    void *left, *right, *root, *max;
    assert(heap);

    right_index = 2 * (index + 1);
    left_index = 2 * index + 1;
    left = left_child(heap, length, size, index);
    right = right_child(heap, length, size, index);
    root = heap + index * size;
    if(left == NULL && right == NULL)
       return;

    if(right == NULL)
        max = maximum(left, root, cmp);
    else if(left == NULL)
        max = maximum(right, root, cmp);
    else
        max = maximum(left, maximum(right, root, cmp), cmp);

    if(cmp(root, max)){ // if maximum is not the root
        memswap(max, root, size);
        h_restore(heap, length, size, left != NULL && left != max ? right_index : left_index, cmp);
    }
}
 
// initialize a heap from a given integer array
void h_init(void *heap, size_t length, size_t size, int (*cmp)(const void *, const void *)){
    assert(heap);

    for(int i = (length-1)/2; i >= 0; i--)
        h_restore(heap, length, size, i, cmp);
}

// heap sort, swapping the i-th from last with the maximum
// restoring the heap property for the first $size - $i nodes of the heap after each swap
void hsort(void *array, size_t length, size_t size, int (*cmp)(const void *, const void *)){
    assert(array);
    h_init(array, length, size, cmp);

    for(int i = length - 1; i > 0; i--){
        memswap(array, array + i * size, size);
        h_restore(array, i, size, 0, cmp);
    }
}
