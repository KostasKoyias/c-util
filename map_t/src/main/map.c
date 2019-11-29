#include <stdio.h>
#include <assert.h>
#include "map.h"

int map_init(void *map, size_t size, int (*clone)(void*, va_list), 
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
        vector_insert(&(m->buckets), 0, NULL, size, clone, cmp, print, destroy);
    return 0;
}

void map_put(void *map, ...){
    va_list props;
    uint64_t key, bucket;
    map_t *m = map;
    assert(map);

    va_start(props, map);
    key = va_arg(props, uint64_t);
    va_end(props);

    va_start(props, map);
    bucket = key % m->buckets.next;
    list_add(vector_get(&(m->buckets), bucket), props, 0);
    va_end(props);
}

void *map_get(void *map, uint64_t key){
    map_t *m = map;
    node_t *node;
    assert(map);

    if((node = list_search(vector_get(&(m->buckets), key % m->buckets.next), &key)) == NULL)
        return NULL;
    return node->data;
}

int map_replace(void *map, void *obj){
    map_t *m = map;
    void *dst;

    assert(map && obj);
    if((dst = map_get(map, m->get_key(obj))) == NULL)
        return -1;

    return ((list_t *)vector_get(&(m->buckets), 0))->init(dst, obj);
}

void map_print(const void *map){
    const map_t *m = map;
    assert(map);
    fprintf(stdout, "\e[1;4mmap\e[0m\n * buckets: %lu\n * load_factor: %.2f\n * content\n",
            m->buckets.next, m->load_factor);
    vector_print((void *)(&(m->buckets)));
}

void map_free(void *map){
    map_t *m = map;
    assert(map);
    vector_free(&(m->buckets));
}