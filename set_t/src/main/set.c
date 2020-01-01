#include <stdio.h>
#include <assert.h>
#include "set.h"

int set_init(void *hash_set, size_t size, uint64_t (*get_key)(const void *), int (*clone)(void*, va_list), 
            int (*cmp)(const void*, const void*), void (*print)(void*), 
            void (*destroy)(void *)){
    set_t *h = hash_set;
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
        vector_insert(&(h->buckets), 0, "bucket", size, clone, cmp, NULL, print, destroy);
    return 0;
}

void set_put(void *hash_set, ...){
    va_list props;
    uint64_t key, bucket;
    set_t *h = hash_set;
    assert(hash_set);

    // get key from properties, it is always the first one
    va_start(props, hash_set);
    key = va_arg(props, uint64_t);
    va_end(props);

    // reset properties pointer to pass into constructor
    va_start(props, hash_set);
    bucket = set_hash(hash_set, key);

    // replace value if there is already a mapping for this key
    if(vset_replace(hash_set, props) < 0){
        h->load++;
        while(set_lf(hash_set) > h->load_factor)
            set_split(hash_set);
        list_add(vector_get(&(h->buckets), bucket), props, 0);
    }
    va_end(props);
}

void *set_get(void *hash_set, uint64_t key){
    set_t *h = hash_set;
    node_t *node;
    assert(hash_set);

    if((node = list_search(vector_get(&(h->buckets), set_hash(hash_set, key)), &key)) == NULL)
        return NULL;
    return node->data;
}

int set_replace(void *hash_set, ...){
    va_list props;
    int rv;

    va_start(props, hash_set);
    rv = vset_replace(hash_set, props);
    va_end(props);
    return rv;
}

int set_remove(void *hash_set, uint64_t key){
    set_t *h = hash_set;
    assert(hash_set);
    return list_delete(vector_get(&(h->buckets), set_hash(hash_set, key)), &key);
}

void set_meta(const void *hash_set){
    const set_t *h = hash_set;
    assert(hash_set);
    fprintf(stdout, "\e[1;4mhash_set\e[0m\n * mappings: %lu\n * buckets: %lu\n * bucket_capacity: %u\n * max_load_factor: %.2f\n"\
                " * current_load: %.2f\n * next split: %hhu\n * hash_functions:\n\t1. key %% %u\n"\
                "\t2. key %% %u\n * content\n", h->load, h->buckets.next, h->bucks_capacity, h->load_factor, 
                (float)h->load/(h->bucks_capacity * h->buckets.next), h->split, h->bucks_num, h->bucks_num * 2);
}

void set_print(const void *hash_set){
    const set_t *h = hash_set;
    set_meta(hash_set);
    vector_print((void *)(&(h->buckets)));
}

void set_display(void *hash_set){
    set_t *h = hash_set;
    node_t *parser;
    assert(hash_set && h->get_key);

    set_meta(hash_set);
    for(uint64_t i = 0; i < h->buckets.next; i++){
        fprintf(stdout, "\e[1;4mBucket-%lu\e[0m: <", i);
        for(parser = ((list_t*)vector_get(&(h->buckets), i))->head; parser != NULL && parser->next != NULL; parser = parser->next)
            fprintf(stdout, "%lu\t", h->get_key(parser->data));
        if(parser != NULL)
            fprintf(stdout, "%lu", h->get_key(parser->data));
        fprintf(stdout, ">\n");        
    }
}

void set_free(void *hash_set){
    set_t *h = hash_set;
    assert(hash_set);
    vector_free(&(h->buckets));
}