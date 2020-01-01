#ifndef _set_H_
#define _set_H_

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


    }set_t;

    // methods exposed in the API
    int set_init(void *, size_t, uint64_t (*)(const void *), int (*)(void*, va_list), 
                 int (*)(const void*, const void*), void (*)(void*), void (*)(void*));
    void set_put(void *, ...);
    void *set_get(void *, uint64_t);
    int set_replace(void *, ...);
    int set_remove(void *, uint64_t);
    void set_print(const void *);
    void set_display(void *);
    void set_free(void *);

    // internal methods used
    int vset_replace(void *, va_list);
    void set_foreach(void *, void (*)(void *));
    void set_split(void *);
    float set_lf(void *);
    uint64_t set_hash(void *, uint64_t);


#endif