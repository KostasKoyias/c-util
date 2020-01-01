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

// reset this heap, letting go of all memory allocated
void heap_free(void *heap){
    heap_t *this = heap;

    vector_free(&(this->vector));
    this->cmp = NULL;
    this->array = NULL;
    this->size = this->length = 0;
}

// return a pointer to the root, the element with the highest priority
void* heap_best(void *heap){
    heap_t *this = heap;
    assert(heap);
    return this->array;
}

// return a pointer to the root, the element with the highest priority
void heap_pop(void *heap){
    heap_t *this = heap;
    assert(heap);

    // swap root with the bottom-most, right-most leaf(last element of heap)
    heap_swap(heap);
    vector_remove(&(this->vector), this->length-1);
    this->length--;

    // restore heap property by swapping with larger child until both of them are smaller/do not exist
    heap_restore(heap, 0);
}

void heap_push(void *heap, ...){
    heap_t *this = heap;
    void *parent, *current;
    va_list props;
    assert(heap);

    // insert the new element in the end of the heap
    va_start(props, heap);
    __vector_insert(&(this->vector), 0, props);
    va_end(props);
    this->array = this->vector.data;
    this->length++;

    // swap with parent until in the appropriate place
    for(int index = this->length-1; index != 0; index = (index-1)/2){
        parent = heap_parent(heap, index);
        current = vector_get(&(this->vector), index);
        
        if(this->cmp(current, parent) > 0)
            memswap(current, parent, this->size);
        else
            break;
    }
}

void heap_sort(void *heap){
    heap_t *this = heap;

    assert(heap);
    hsort(this->array, this->length, this->size, this->cmp);
}