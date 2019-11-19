#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

int memswap(void* a, void *b, size_t size){
    void *tmp;
    int rv = 0;
    assert(a && b);

    if((tmp = malloc(size)) == NULL)
        return -1;

    if(memcpy(tmp, a, size) == NULL)
        rv = -2;
    else if(memcpy(a, b, size) == NULL)
        rv = -3;
    else if(memcpy(b, tmp, size) == NULL)
        rv = -4;

    free(tmp);
    return rv;
}

void reset(void *ptr){
    if(ptr != NULL){
        free(ptr);
        ptr = NULL;
    }
}