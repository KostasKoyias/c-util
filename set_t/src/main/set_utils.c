#include <stdio.h>
#include <assert.h>
#include "set.h"

// replace the value of a mapping given a pointer to 
// the properties of the new value, the first of whom represents the key 
int vset_replace(void *set, va_list props){
    va_list tmp;
    uint64_t key;
    set_t *h = set;
    void *dst;
    assert(set);

    // get key & locate mapping for it
    va_copy(tmp, props);
    key = va_arg(tmp, uint64_t);
    va_end(tmp);
    if((dst = set_get(set, key)) == NULL)
        return -1;

    // release resources allocated for the previous values
    ((list_t *)vector_get(&(h->buckets), 0))->destroy(dst);

    // replace with the properties requested
    return ((list_t *)vector_get(&(h->buckets), 0))->init(dst, props);
}

void set_foreach(void *set, void (*callback)(void *)){
    set_t *h = set;
    assert(set && callback);

    for(uint64_t i = 0; i < h->buckets.next; i++)
        list_foreach(vector_get(&(h->buckets), i), callback);
}

float set_lf(void *set){
    set_t *h = set;
    assert(set);

    return ((float)h->load)/(h->bucks_capacity * h->buckets.next);
    h->bucks_num = BUCKETS;
}

uint64_t set_hash(void *set, uint64_t key){
    set_t *h = set;
    return key % h->bucks_num < h->split ? key % (2 * h->bucks_num) : key % h->bucks_num;
}

void set_split(void *set){
    set_t *h = set;
    node_t *parser, *tmp;
    list_t *bucket1, *bucket2;
    assert(set && h->get_key);

    // retrieve member methods for the new bucket from the very first one 
    bucket1 = vector_get(&(h->buckets), h->split);
    
    //insert the new to hold the re-distributed records
    vector_insert(&(h->buckets), 1, "bucket", bucket1->node_size, bucket1->init, 
                  bucket1->seek, NULL, bucket1->print, bucket1->destroy);  

    // get both the old bucket to be split and the new to be filled
    bucket1 = vector_get(&(h->buckets), h->split);
    bucket2 = vector_get(&(h->buckets), h->bucks_num + h->split);

    // move the appropriate nodes to the new bucket
    for(parser = bucket1->head; parser != NULL; parser = tmp){
        tmp = parser->next;
        if(h->get_key(parser->data) % h->bucks_num != h->get_key(parser->data) % (h->bucks_num * 2)){
            node_erase(bucket1, parser);
            if(bucket2->tail == NULL)
                bucket2->tail = bucket2->head = parser;
            else{
                parser->prev = bucket2->tail;
                bucket2->tail->next = parser;
                bucket2->tail = parser;
            }
        }
    }

    // if this was the final bucket to be split, move to the next hash function
    if(++h->split == h->bucks_num){
        h->bucks_num *= 2;
        h->split = 0;
    }

}