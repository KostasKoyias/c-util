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
void* left_child(void *heap, int index){
    heap_t *hp = heap;
    assert(heap);

    return (2 * index + 1 < hp->length) ? hp->array + hp->size * (2 * index + 1) : NULL;
}

// get the right child of a node in an array-represented heap, by node index
void* right_child(void *heap, int index){
    heap_t *hp = heap;
    assert(heap);

    return (2 * (index + 1) < hp->length) ? hp->array + hp->size * (2 * (index + 1)) : NULL;
}

// initialize a heap from an existing array
void __heap_init(void *heap, void *array, size_t length, size_t size,
                int (*init)(void *, va_list), int (*cmp)(const void*, const void*), void (*destroy)(void *)){

        heap_t *this = heap;
        assert(heap);
        
        vector_init(&(this->vector), length, size, init, NULL, cmp, NULL, NULL, destroy);

        for(int i = 0; i < length; i++)
            vector_insert(&(this->vector), 1, array + i * size);
        this->array = this->vector.data;
}

// heap sort in-place without creating a copy, swapping the i-th from last with the maximum
// restoring the heap property for the first $size - $i nodes of the heap after each swap
void hsort(void *array, size_t length, size_t size, int (*cmp)(const void *, const void *)){
    heap_t heap;
    assert(array && cmp);
    heap_init(&heap, array, length, size, SHALLOW, NULL, cmp, NULL);

    for(heap.length = length-1; heap.length > 0; heap.length--){
        memswap(heap.array, heap.array + heap.length * size, size);
        heap_restore(&heap, 0);
    }

    heap.length = length;
}