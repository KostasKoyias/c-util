#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _vector_H
#define _vector_H
    #define MIN_ELEMENTS 2

    typedef struct vector{
        void *data;
        size_t size;
        uint64_t next;
        uint64_t capacity;

        int (*init)(void *, va_list);
        int (*seek)(const void *, const void *);
        int (*cmp)(const void *, const void *);
        void (*clone)(void*, const void*);
        void (*print)(void *);
        void (*destroy)(void *);
    }vector_t;

    // basic methods
    int vector_init(void*, int, size_t, int (*)(void *, va_list), 
                    int (*)(const void*, const void*), int (*)(const void*, const void*),
                    void (*)(void*, const void*), void (*)(void *), void (*)(void *));
    int vector_insert(void*, int, ...);
    void *vector_get(void*, uint64_t);
    void *vector_seek(void*, const void*, uint64_t*);
    int vector_isfull(const void *);
    int vector_remove(void *, const uint64_t);
    int vector_delete(void *, const void *);
    void vector_print(void *);
    void vector_shrink(void*);
    void vector_free(void*);

    // utilities and advanced methods
    void vector_reverse(void *);
    void vector_qsort(void *);
    void *vector_bsearch(void *, ...);
    void vector_reduce(void *, void *, void (*)(void*, void*));
    void vector_foreach(void *, void (*)(void *));
    int vector_cmp(const void *, const void *);
    void vector_clone(void *, const void*);

#endif