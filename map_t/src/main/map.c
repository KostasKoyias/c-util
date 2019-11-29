#include <stdio.h>
#include <assert.h>
#include "map.h"

int map_init(void *map, size_t size, uint64_t (*get_key)(const void *), int (*clone)(void*, va_list), 
            int (*cmp)(const void*, const void*), void (*print)(void*), 
            void (*destroy)(void *)){
    map_t *m = map;
    assert(map && get_key);

    m->load = m->split = 0; // next bucket to be split when #records/(#buckets * bucket_capacity) > load_factor
    m->load_factor = LOAD_FACTOR; 
    m->bucks_capacity = CAPACITY;
    m->bucks_num = BUCKETS;
    m->destroy = destroy ? destroy : free;
    m->get_key = get_key;

    // initialize a list vector where each list represents a bucket
    vector_init(&(m->buckets), m->bucks_num, sizeof(list_t), list_init_wrap, NULL, NULL, NULL, list_print, list_free);
    for(int i = 0; i < m->buckets.capacity; i++)
        vector_insert(&(m->buckets), 0, "bucket", size, clone, cmp, print, destroy);
    return 0;
}

void map_put(void *map, ...){
    va_list props;
    uint64_t key, bucket;
    map_t *m = map;
    assert(map);

    // get key from properties, it is always the first one
    va_start(props, map);
    key = va_arg(props, uint64_t);
    va_end(props);

    // reset properties pointer to pass into constructor
    va_start(props, map);
    bucket = map_hash(map, key);

    // replace value if there is already a mapping for this key
    if(vmap_replace(map, props) < 0){
        m->load++;
        while(map_lf(map) > m->load_factor)
            map_split(map);
        list_add(vector_get(&(m->buckets), bucket), props, 0);
    }
    va_end(props);
}

void *map_get(void *map, uint64_t key){
    map_t *m = map;
    node_t *node;
    assert(map);

    if((node = list_search(vector_get(&(m->buckets), map_hash(map, key)), &key)) == NULL)
        return NULL;
    return node->data;
}

int map_replace(void *map, ...){
    va_list props;
    int rv;

    va_start(props, map);
    rv = vmap_replace(map, props);
    va_end(props);
    return rv;
}

int map_remove(void *map, uint64_t key){
    map_t *m = map;
    assert(map);
    return list_delete(vector_get(&(m->buckets), map_hash(map, key)), &key);
}

void map_meta(const void *map){
    const map_t *m = map;
    assert(map);
    fprintf(stdout, "\e[1;4mmap\e[0m\n * mappings: %lu\n * buckets: %lu\n * bucket_capacity: %u\n * max_load_factor: %.2f\n"\
                " * current_load: %.2f\n * next split: %hhu\n * hash_functions:\n\t1. key %% %u\n"\
                "\t2. key %% %u\n * content\n", m->load, m->buckets.next, m->bucks_capacity, m->load_factor, 
                (float)m->load/(m->bucks_capacity * m->buckets.next), m->split, m->bucks_num, m->bucks_num * 2);
}

void map_print(const void *map){
    const map_t *m = map;
    map_meta(map);
    vector_print((void *)(&(m->buckets)));
}

void map_display(void *map){
    map_t *m = map;
    node_t *parser;
    assert(map && m->get_key);

    map_meta(map);
    for(uint64_t i = 0; i < m->buckets.next; i++){
        fprintf(stdout, "\e[1;4mBucket-%lu\e[0m: <", i);
        for(parser = ((list_t*)vector_get(&(m->buckets), i))->head; parser != NULL && parser->next != NULL; parser = parser->next)
            fprintf(stdout, "%lu\t", m->get_key(parser->data));
        if(parser != NULL)
            fprintf(stdout, "%lu", m->get_key(parser->data));
        fprintf(stdout, ">\n");        
    }
}

void map_free(void *map){
    map_t *m = map;
    assert(map);
    vector_free(&(m->buckets));
}