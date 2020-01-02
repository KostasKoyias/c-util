#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

/*
 * merge-sort methods
 */ 
void msort(void *, size_t, size_t, int (*)(const void *, const void *));
void __msort(void *, void *, size_t, size_t, size_t, int (*)(const void *, const void *));
void __merge(void *, void *, size_t, size_t, size_t, int (*)(const void *, const void *));

void msort(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *)){
    void *helper = malloc(n * size);
    __msort(base, helper, 0, n-1, size, cmp);
    free(helper);
}

void __msort(void *base, void *helper, size_t start, size_t end, size_t size, 
                  int (*cmp)(const void *, const void *)){
    size_t middle;
    assert(base && cmp);

    // base case
    if(start >= end)
        return;

    middle = (start + end)/2;
    __msort(base, helper, start, middle, size, cmp);
    __msort(base, helper, middle + 1, end, size, cmp);
    __merge(base, helper, start, end, size, cmp);

}

void __merge(void *base, void *helper, size_t start, size_t end, size_t size, int (*cmp)(const void *, const void *)){
    size_t i, j, middle, count;
    assert(base && cmp);

    // initialize indexes
    middle = (start + end)/2;
    i = start;
    j = middle + 1;
    count = 0;

    // insert the smallest of 2 element into the next position available
    while(i < middle + 1 && j < end + 1){

        if(cmp(base + i * size, base + j * size) < 0)
            memcpy(helper + count * size, base + (i++) * size, size);
        else
            memcpy(helper + count * size, base + (j++) * size, size);
        count++;
    }

    // copy the remaining parts
    memcpy(helper + count * size, base + i * size, size * (middle + 1 - i));
    memcpy(helper + count * size, base + j * size, size * (end + 1 - j));

    // copy back to base
    memcpy(base + start * size, helper, (end + 1 - start) * size);
}