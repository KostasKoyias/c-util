#ifndef _map_H_
#define _map_H_

    #include <stdint.h>
    #include "list.h"
    #include "vector.h"

    #define LOAD_FACTOR .75
    #define CAPACITY 2

    typedef struct map{
        vector_t buckets;
        uint8_t load_factor;

        uint64_t (*get_key)(const void*);
        void (*destroy)(void*);

    }map_t;

    int map_init(void *, size_t, int (*)(void*, va_list), int (*)(const void*, const void*), 
                 void (*)(void*), uint64_t (*)(const void*), void (*)(void*));
    void map_insert(void *, const void *);
    void map_print(const void *);
    void map_free(void *);

#endif