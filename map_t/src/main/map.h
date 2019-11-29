#ifndef _map_H_
#define _map_H_

    #include <stdint.h>
    #include "list.h"
    #include "vector.h"

    #define LOAD_FACTOR 0.75
    #define CAPACITY 2

    typedef struct map{
        vector_t buckets;
        float load_factor;

        void (*destroy)(void*);

    }map_t;

    int map_init(void *, size_t, int (*)(void*, va_list), 
                 int (*)(const void*, const void*), void (*)(void*), void (*)(void*));
    void map_put(void *, ...);
    void *map_get(void *, uint64_t);
    int map_replace(void *, ...);
    int map_remove(void *, uint64_t);
    void map_foreach(void *, void (*)(void *));
    void map_print(const void *);
    void map_free(void *);

#endif