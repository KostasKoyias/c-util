#include <string.h>
#include <assert.h>
#include "vector.h"
#include "utils.h"

void vector_foreach(void *vector, void (*callback)(void *)){
    vector_t *v = vector;
    assert(vector && callback);
    for(int i = 0; i < v->next; i++)
        callback(v->data + i * v->size);
}

void vector_reduce(void *vector, void *start, void (*reducer)(void*, void*)){
    vector_t *v = vector;
    assert(vector && reducer);
    for(int i = 0; i < v->next; i++)
        reducer(start, v->data + i * v->size);
}

void vector_qsort(void *vector){
    vector_t *v = vector;
    assert(vector && v->cmp);
    qsort(v->data, v->next, v->size, v->cmp);
}

void *vector_bsearch(void *vector, ...){
    vector_t *v = vector;
    void *obj, *rv;
    va_list props;
    assert(vector && v->init && v->cmp);

    // create an object to look for in the vector
    va_start(props, vector);
    obj = malloc(v->size);
    v->init(obj, props);
    va_end(props);

    // use binary search to locate the object, vector must be sorted
    rv = bsearch(obj, v->data, v->next, v->size, v->cmp);

    // free temporary object created for the search
    if(v->destroy)
        v->destroy(obj);
    reset(obj);
    return rv;
}

void vector_reverse(void *vector){
    vector_t *v = vector;
    assert(vector);

    for(int i = 0; i < v->next/2; i++)
        memswap(v->data + i * v->size, v->data + (v->next - (i + 1)) * v->size, v->size);
}

int vector_cmp(const void *a, const void *b){
    const vector_t *va = a, *vb = b;
    int diff;

    // vector item types compared should be of the same size and having the exact same comparator
    assert(a && b && va->cmp == vb->cmp && va->size == vb->size);

    if(va->next != vb->next)
        return va->next - vb->next;

    // if any of their elements is not equal return the corresponding difference
    for(int i = 0; i < va->next; i++){
        if((diff = va->cmp(va->data + i * va->size, vb->data + i * vb->size)) != 0)
            return diff;
    }

    return 0;
}

void vector_clone(void *dst, const void *src){
    vector_t *vdst = dst;
    const vector_t *vsrc = src;
    void *item_src, *item_dst;
    int i, max;
    assert(dst && src && vsrc->clone);

    vector_init(vdst, vsrc->size, vsrc->init, vsrc->cmp, vsrc->seek, vsrc->clone, vsrc->print, vsrc->destroy);
    for(i = 0, max = MIN_ELEMENTS; i < vsrc->next; vdst->next++, i++){
        if(i + 1 == max){
            max *= 2;
            vdst->data = realloc(vdst->data, vdst->size * max);
        }

        item_src = vsrc->data + i * vsrc->size;
        item_dst = vdst->data + i * vdst->size;
        vdst->clone(item_dst, item_src);
    }
}