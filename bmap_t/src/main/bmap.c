#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "bmap.h"
#include "utils.h"

#define MOD_OPS 3
enum operation{SET, RESET, TOGGLE, GET};

void bmap_init(void *bmap, uint32_t bits){
    bmap_t *this = bmap;
    size_t bytes;

    assert(bmap);
    this->bits = bits;

    // allocate enough byte space to hold all bits
    bytes = ceil((double)bits/BYTE_TO_BITS);
    this->data = calloc(bytes, 1);
}
    
int8_t bmap_op(void *bmap, uint32_t pos, uint8_t op){
    bmap_t *this = bmap;
    uint32_t byte, index;
    uint8_t *data;
    void (*ops[MOD_OPS])(uint8_t *, uint8_t) = {set_bit, reset_bit, toggle_bit};
    assert(bmap);

    // ensure position requested is within bounds
    if(this->bits <= pos)
        return -1;

    // get byte number of where the requested bit is stored
    byte = pos / BYTE_TO_BITS;

    // point to that byte
    data = this->data + byte;

    // get the index of the requested bit in that byte
    index = pos % BYTE_TO_BITS;

    if(op == GET)
        return (int8_t)get_bit(*data, index);

    ops[op](data, index);
    return 0;
}

int8_t bmap_get(void *bmap, uint32_t pos){
    return bmap_op(bmap, pos, GET);
}

int8_t bmap_set(void *bmap, uint32_t pos){
    return bmap_op(bmap, pos, SET);
}

int8_t bmap_reset(void *bmap, uint32_t pos){
    return bmap_op(bmap, pos, RESET);
}

int8_t bmap_toggle(void *bmap, uint32_t pos){
    return bmap_op(bmap, pos, TOGGLE);
}

// print a bit map bit-by-bit
void bmap_print(const void *bmap){
    const bmap_t *this = bmap;
    uint32_t rem, byte;
    char *str;
    
    assert(bmap);

    for(rem = this->bits, byte = 0; rem > BYTE_TO_BITS; rem -= BYTE_TO_BITS, byte++)
        fprintf(stdout, "%s - ", str_reverse(byte_to_bits(*(this->data + byte))));
    if(rem > 0){
        str = str_reverse(byte_to_bits(*(this->data + byte)));
        str[rem] = '\0';
        fprintf(stdout, "%s\n", str);
    }
}

// let go of resources allocated
void bmap_free(void *bmap){
    bmap_t *this = bmap;

    assert(bmap);
    free(this->data);
    this->bits = 0;
}
