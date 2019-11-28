#include <stdio.h>
#include <assert.h>
#include "map.h"

int map_init(void *map, size_t size, int (*init)(void*, va_list), 
            int (*cmp)(const void*, const void*), void (*print)(void*),
            uint64_t (*get_key)(const void*), void (*destroy)(void *)){
    map_t *m = map;
    assert(map && get_key);

    m->get_key = get_key;
    m->load_factor = LOAD_FACTOR;
    m->destroy = destroy ? destroy : free;

    // initialize a list vector where each list represents a bucket
    vector_init(&(m->buckets), CAPACITY, sizeof(list_t), list_init_wrap, NULL, NULL, NULL, list_print, list_free);
    for(int i = 0; i < m->buckets.capacity; i++)
        vector_insert(&(m->buckets), 0, NULL, size, init, cmp, print, destroy);
    return 0;
}

void map_insert(void *map, const void *obj){
    map_t *m = map;
    assert(map && obj);
}

void map_print(const void *map){
    const map_t *m = map;
    assert(map);
    fprintf(stdout, "\e[1;4mmap\e[0m\n *buckets: %lu\n *load_factor: %hhu\n",
            m->buckets.next, m->load_factor);
    vector_print((void *)(&(m->buckets)));
}

void map_free(void *map){
    map_t *m = map;
    assert(map);
    vector_free(&(m->buckets));
}