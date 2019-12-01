#include <stdio.h>
#include <assert.h>
#include "hset.h"

int hset_init(void *hash_set, size_t size, uint64_t (*get_key)(const void *), int (*clone)(void*, va_list), 
            int (*cmp)(const void*, const void*), void (*print)(void*), 
            void (*destroy)(void *)){
    hset_t *h = hash_set;
    assert(hash_set && get_key);

    h->load = h->split = 0; // next bucket to be split when #records/(#buckets * bucket_capacity) > load_factor
    h->load_factor = LOAD_FACTOR; 
    h->bucks_capacity = CAPACITY;
    h->bucks_num = BUCKETS;
    h->destroy = destroy ? destroy : free;
    h->get_key = get_key;

    // initialize a list vector where each list represents a bucket
    vector_init(&(h->buckets), h->bucks_num, sizeof(list_t), list_init_wrap, NULL, NULL, NULL, list_print, list_free);
    for(int i = 0; i < h->buckets.capacity; i++)
        vector_insert(&(h->buckets), 0, "bucket", size, clone, cmp, print, destroy);
    return 0;
}

void hset_put(void *hash_set, ...){
    va_list props;
    uint64_t key, bucket;
    hset_t *h = hash_set;
    assert(hash_set);

    // get key from properties, it is always the first one
    va_start(props, hash_set);
    key = va_arg(props, uint64_t);
    va_end(props);

    // reset properties pointer to pass into constructor
    va_start(props, hash_set);
    bucket = hset_hash(hash_set, key);

    // replace value if there is already a mapping for this key
    if(vhset_replace(hash_set, props) < 0){
        h->load++;
        while(hset_lf(hash_set) > h->load_factor)
            hset_split(hash_set);
        list_add(vector_get(&(h->buckets), bucket), props, 0);
    }
    va_end(props);
}

void *hset_get(void *hash_set, uint64_t key){
    hset_t *h = hash_set;
    node_t *node;
    assert(hash_set);

    if((node = list_search(vector_get(&(h->buckets), hset_hash(hash_set, key)), &key)) == NULL)
        return NULL;
    return node->data;
}

int hset_replace(void *hash_set, ...){
    va_list props;
    int rv;

    va_start(props, hash_set);
    rv = vhset_replace(hash_set, props);
    va_end(props);
    return rv;
}

int hset_remove(void *hash_set, uint64_t key){
    hset_t *h = hash_set;
    assert(hash_set);
    return list_delete(vector_get(&(h->buckets), hset_hash(hash_set, key)), &key);
}

void hset_meta(const void *hash_set){
    const hset_t *h = hash_set;
    assert(hash_set);
    fprintf(stdout, "\e[1;4mhash_set\e[0m\n * mappings: %lu\n * buckets: %lu\n * bucket_capacity: %u\n * max_load_factor: %.2f\n"\
                " * current_load: %.2f\n * next split: %hhu\n * hash_functions:\n\t1. key %% %u\n"\
                "\t2. key %% %u\n * content\n", h->load, h->buckets.next, h->bucks_capacity, h->load_factor, 
                (float)h->load/(h->bucks_capacity * h->buckets.next), h->split, h->bucks_num, h->bucks_num * 2);
}

void hset_print(const void *hash_set){
    const hset_t *h = hash_set;
    hset_meta(hash_set);
    vector_print((void *)(&(h->buckets)));
}

void hset_display(void *hash_set){
    hset_t *h = hash_set;
    node_t *parser;
    assert(hash_set && h->get_key);

    hset_meta(hash_set);
    for(uint64_t i = 0; i < h->buckets.next; i++){
        fprintf(stdout, "\e[1;4mBucket-%lu\e[0m: <", i);
        for(parser = ((list_t*)vector_get(&(h->buckets), i))->head; parser != NULL && parser->next != NULL; parser = parser->next)
            fprintf(stdout, "%lu\t", h->get_key(parser->data));
        if(parser != NULL)
            fprintf(stdout, "%lu", h->get_key(parser->data));
        fprintf(stdout, ">\n");        
    }
}

void hset_free(void *hash_set){
    hset_t *h = hash_set;
    assert(hash_set);
    vector_free(&(h->buckets));
}