#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "vector.h"
#include "utils.h"

int vector_init(void *vector, size_t size, 
                int (*init)(void *, va_list), int (*seek)(const void*, const void*),
                int (*cmp)(const void*, const void*), void (*clone)(void*, const void*),
                void (*print)(void *), void (*destroy)(void *)){
    vector_t *v = vector;
    assert(vector && init);
    if(size < 0)
        return -1;

    // meta-data
    v->next = 0;
    v->capacity = MIN_ELEMENTS;
    v->size = size;

    // actual content
    v->data = calloc(MIN_ELEMENTS, v->size);

    // member methods
    v->init = init;
    v->seek = seek; // find by some unique field given only it's value, not the whole object
    v->cmp = cmp;   // compare two instances of this type, complete objects are used here
    v->clone = clone;
    v->print = print;
    v->destroy = destroy;
    return MIN_ELEMENTS;
}

int vector_insert(void *vector, int single, ...){
    vector_t *v = vector;
    va_list props;
    assert(vector);

    // double vector capacity if full
    if(vector_isfull(vector)){
        v->capacity = single ? v->capacity + 1 : v->capacity * 2;
        v->data = realloc(v->data, v->size * v->capacity);
    }

    // use the appropriate constructor to initialize the new item
    va_start(props, single);
    v->init(v->data + ((v->next++) * v->size), props);
    va_end(props);
    return 0;
}

int vector_remove(void *vector, const uint64_t index){
    vector_t *v= vector;
    assert(vector);

    if(v->next <= index)
        return -1;

    // destroy element in the specified position
    if(v->destroy)
        v->destroy(v->data + index * v->size);

    // shift all elements one position to the left
    for(uint64_t i = index; i < v->next - 1; i++)
        memcpy(v->data + i * v->size, v->data + (i+1) * v->size, v->size);
    v->next--;

    return 0;
}

int vector_delete(void *vector, const void *key){
    uint64_t pos; 
    assert(vector && key);

    // get position of the first matching element
    if(vector_seek(vector, key, &pos) == NULL) 
        return -1;
    
    return vector_remove(vector, pos);
}

void *vector_get(void *vector, uint64_t index){
    vector_t *v = vector;
    assert(vector);
    if(index >= v->next)
        return NULL;
    
    return v->data + index * v->size;
}

void *vector_seek(void *vector, const void *key, uint64_t *pos){
    vector_t *v = vector;
    void *item;
    assert(vector && key && v->seek);

    for(int i = 0; i < v->next; i++){
        item = v->data + i * v->size;
        if(v->seek(item, key)){

            // store position of the matching item & return a pointer to it
            if(pos != NULL)
                *pos = i;
            return item;
        }
    }

    return NULL;
}

void vector_print(void *vector){
    vector_t *v = vector;
    assert(vector && v->print);

    // display meta-data
    fprintf(stdout, "\e[1;4mVector\e[0m\n * type size:\t%ld bytes\n * next:\t%lu\n * capacity:\t%lu\n * content\n",
            v->size, v->next, v->capacity);

    // use the appropriate print function to showcase each item
    if(v->print)
        vector_foreach(v, v->print);
    else
        fprintf(stdout, "No printing method provided for this data type\n");
}

void vector_shrink(void *vector){
    vector_t *v = vector;
    assert(vector);

    if(!vector_isfull(vector)){
        v->data = realloc(v->data, v->next * v->size);
        v->capacity = v->next;
    }
}

// destroy a vector, letting go of all resources allocated
void vector_free(void *vector){
    vector_t *v = vector;
    assert(vector);

    // let go of all space allocated for each item in this vector
    if(v->destroy)
        vector_foreach(vector, v->destroy);

    reset(v->data);
    v->next = v->capacity = v->size = 0;
}

int vector_isfull(const void *vector){
    const vector_t *v = vector;
    assert(vector);
    return v->next == v->capacity;
}