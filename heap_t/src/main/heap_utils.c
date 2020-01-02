#include <assert.h>
#include <string.h>
#include "utils.h"
#include "heap.h"

/*
 * heap utility/helper methods
 */ 
// get the maximum of 2 based on the comparator provided
void* maximum(void *a, void *b, int (*cmp)(const void *, const void *)){
    assert(a && b);
    return cmp(a, b) > 0 ? a : b;
}

// get the left child of a node in an array-represented heap, by node index
void* heap_left_child(void *heap, int index){
    heap_t *this = heap;
    assert(heap);

    return (2 * index + 1 < this->length) ? this->array + this->size * (2 * index + 1) : NULL;
}

// get the right child of a node in an array-represented heap, by node index
void* heap_right_child(void *heap, int index){
    heap_t *this = heap;
    assert(heap);

    return (2 * (index + 1) < this->length) ? this->array + this->size * (2 * (index + 1)) : NULL;
}

// get the parent of an element by index
void* heap_parent(void *heap, int index){
    heap_t *this = heap;
    assert(heap);

    return index > 0 ? vector_get(&(this->vector), (index - 1)/2): NULL;
}

void heap_insert(void *heap, void *value){
    heap_t *this = heap;
    assert(heap);

    vector_insert(&(this->vector), 0, value);
    this->array = this->vector.data;
}

// initialize a heap from an existing array
void __heap_init(void *heap, void *array, size_t length, size_t size,
                int (*init)(void *, va_list), int (*cmp)(const void*, const void*), void (*destroy)(void *)){

        heap_t *this = heap;
        assert(heap);
        
        vector_init(&(this->vector), length, size, init, NULL, cmp, NULL, NULL, destroy);
        for(int i = 0; i < length; i++)
            heap_insert(heap, array + i *size); 
}

// heap sort in-place without creating a copy, 
void hsort(void *array, size_t length, size_t size, int (*cmp)(const void *, const void *)){
    heap_t heap;
    assert(array && cmp);
    heap_init(&heap, array, length, size, SHALLOW, NULL, cmp, NULL);
    heap_sort(&heap);
}

// heap-sort by swapping the i-th from last with the maximum
// restoring the heap property for the first $size - $i nodes of the heap after each swap
void heap_sort(void *heap){
    int length;
    heap_t *this = heap;
    assert(heap);
    
    for(length = this->length, this->length = length-1; this->length > 0; this->length--){
        memswap(this->array, this->array + this->length * this->size, this->size);
        heap_restore(this, 0);
    }

    this->length = length;
}

// swap root element with the bottom-most, right-most leaf
void heap_swap(void *heap){
    heap_t *this = heap;
    memmove(this->vector.data, this->vector.data + this->size * (this->length-1), this->size);
}