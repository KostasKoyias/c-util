#ifndef _map_H_
#define _map_H_

    #include <stdint.h>
    #include "list.h"
    #include "vector.h"

    #define LOAD_FACTOR 0.75
    #define BUCKETS 2
    #define CAPACITY 16

    typedef struct map{
        vector_t buckets;
        uint8_t bucks_capacity;
        uint32_t bucks_num;

        float load_factor;
        uint32_t split;
        uint64_t load;
        void (*destroy)(void*);
        uint64_t (*get_key)(const void*);


    }map_t;

    // methods exposed in the API
    int map_init(void *, size_t, uint64_t (*)(const void *), int (*)(void*, va_list), 
                 int (*)(const void*, const void*), void (*)(void*), void (*)(void*));
    void map_put(void *, ...);
    void *map_get(void *, uint64_t);
    int map_replace(void *, ...);
    int map_remove(void *, uint64_t);
    void map_print(const void *);
    void map_display(void *);
    void map_free(void *);

    // internal methods used
    int vmap_replace(void *, va_list);
    void map_foreach(void *, void (*)(void *));
    void map_split(void *);
    float map_lf(void *);
    uint64_t map_hash(void *, uint64_t);


#endif