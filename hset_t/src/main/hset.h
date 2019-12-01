#ifndef _hset_H_
#define _hset_H_

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


    }hset_t;

    // methods exposed in the API
    int hset_init(void *, size_t, uint64_t (*)(const void *), int (*)(void*, va_list), 
                 int (*)(const void*, const void*), void (*)(void*), void (*)(void*));
    void hset_put(void *, ...);
    void *hset_get(void *, uint64_t);
    int hset_replace(void *, ...);
    int hset_remove(void *, uint64_t);
    void hset_print(const void *);
    void hset_display(void *);
    void hset_free(void *);

    // internal methods used
    int vhset_replace(void *, va_list);
    void hset_foreach(void *, void (*)(void *));
    void hset_split(void *);
    float hset_lf(void *);
    uint64_t hset_hash(void *, uint64_t);


#endif