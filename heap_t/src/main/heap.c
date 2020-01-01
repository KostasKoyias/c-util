#include <string.h>
#include <assert.h>
#include "heap.h"
#include "utils.h"

/*
 * heap member methods
 */ 
// restore the heap property in the sub-tree starting at $index
void heap_restore(void *heap, int index){
    heap_t *this = heap;
    int right_index, left_index;
    void *left, *right, *root, *max;
    assert(heap);

    right_index = 2 * (index + 1);
    left_index = 2 * index + 1;
    left = left_child(heap, index);
    right = right_child(heap, index);
    root = this->array + index * this->size;
    if(left == NULL && right == NULL)
       return;

    if(right == NULL)
        max = maximum(left, root, this->cmp);
    else if(left == NULL)
        max = maximum(right, root, this->cmp);
    else
        max = maximum(left, maximum(right, root, this->cmp), this->cmp);

    if(root != max){ // if maximum is not the root
        memswap(max, root, this->size);
        heap_restore(heap, left == NULL || left != max ? right_index : left_index);
    }
}
 
// initialize a heap from a given integer array
void heap_init(void *heap, void *array, size_t length, size_t size, int copy,
                int (*init)(void *, va_list), int (*cmp)(const void*, const void*), void (*destroy)(void *)){
    heap_t *this = heap;
    assert(heap);

    if(copy == SHALLOW)
        this->array = array;
    else
        __heap_init(heap, array, length, size, init, cmp, destroy);

    this->length = length;
    this->size = size;
    this->cmp = cmp;
    for(int i = (length-1)/2; i >= 0; i--)
        heap_restore(this, i);
}

int heap_isempty(void *heap){
    heap_t *this = heap;
    assert(heap);

    return this->vector.next == 0;
}

void heap_free(void *heap){
    heap_t *this = heap;

    vector_free(&(this->vector));
    this->cmp = NULL;
    this->array = NULL;
    this->size = this->length = 0;
}