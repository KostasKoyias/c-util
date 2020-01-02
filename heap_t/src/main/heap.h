#ifndef _heap_H
#define _heap_H

    #include <stdlib.h>
    #include "vector.h"
    #define SHALLOW 0
    #define DEEP 1
    int print(const int *, int);

    typedef struct heap{
        void *array;
        vector_t vector;
        size_t length;
        size_t size;
        int (*cmp)(const void *, const void *);
    }heap_t;

    // heap utilities -- helper/hidden methods
    void *maximum(void *, void*, int (*)(const void *, const void *));
    void heap_swap(void *);
    void hsort(void *, size_t, size_t, int (*)(const void *, const void *)); // sort in-place
    void heap_restore(void *, int);
    void __heap_init(void *, void *, size_t, size_t, 
                  int (*)(void *, va_list), int (*)(const void*, const void*), void (*)(void *));

    // heap traversal helper methods
    void *heap_parent(void *, int);
    void *heap_left_child(void *, int);
    void *heap_right_child(void *, int);

    // heap member methods
    void heap_init(void *, void *, size_t, size_t, int, 
                  int (*)(void *, va_list), int (*)(const void*, const void*), void (*)(void *));
    void heap_free(void *);
    int heap_isempty(void *);
    void heap_sort(void *);
    void* heap_best(void *);
    void heap_push(void *, ...);
    void heap_pop(void *);

#endif 