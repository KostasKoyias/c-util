#include <stdio.h>
#include <assert.h>
#include "map.h"

// replace the value of a mapping given a pointer to 
// the properties of the new value, the first of whom represents the key 
int vmap_replace(void *map, va_list props){
    va_list tmp;
    uint64_t key;
    map_t *m = map;
    void *dst;
    assert(map);

    // get key & locate mapping for it
    va_copy(tmp, props);
    key = va_arg(tmp, uint64_t);
    va_end(tmp);
    if((dst = map_get(map, key)) == NULL)
        return -1;

    // release resources allocated for the previous values
    ((list_t *)vector_get(&(m->buckets), 0))->destroy(dst);

    // replace with the properties requested
    return ((list_t *)vector_get(&(m->buckets), 0))->init(dst, props);
}

void map_foreach(void *map, void (*callback)(void *)){
    map_t *m = map;
    assert(map && callback);

    for(uint64_t i = 0; i < m->buckets.next; i++)
        list_foreach(vector_get(&(m->buckets), i), callback);
}

float map_lf(void *map){
    map_t *m = map;
    assert(map);

    return ((float)m->load)/(m->bucks_capacity * m->buckets.next);
    m->bucks_num = BUCKETS;
}

uint64_t map_hash(void *map, uint64_t key){
    map_t *m = map;
    return key % m->bucks_num < m->split ? key % (2 * m->bucks_num) : key % m->bucks_num;
}

void map_split(void *map){
    map_t *m = map;
    node_t *parser, *tmp;
    list_t *bucket1, *bucket2;
    assert(map && m->get_key);

    // retrieve member methods for the new bucket from the very first one 
    bucket1 = vector_get(&(m->buckets), m->split);
    
    //insert the new to hold the re-distributed records
    vector_insert(&(m->buckets), 1, "bucket", bucket1->node_size, bucket1->init, 
                  bucket1->cmp, bucket1->print, bucket1->destroy);  

    // get both the old bucket to be split and the new to be filled
    bucket1 = vector_get(&(m->buckets), m->split);
    bucket2 = vector_get(&(m->buckets), m->bucks_num + m->split);

    // move the appropriate nodes to the new bucket
    for(parser = bucket1->head; parser != NULL; parser = tmp){
        tmp = parser->next;
        if(m->get_key(parser->data) % m->bucks_num != m->get_key(parser->data) % (m->bucks_num * 2)){
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
    if(++m->split == m->bucks_num){
        m->bucks_num *= 2;
        m->split = 0;
    }

}