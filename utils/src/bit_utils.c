#include <stdlib.h>
#include "utils.h"

// return a random number of $bits bits
uint64_t rand_bits(uint8_t bits){
    uint8_t i;
    uint64_t num;
    for(i = 0, num = 0; i < bits; i++)
        num += (num << 1) + (rand() % 2);
    return num;
}

void set_bit(uint8_t *map, uint8_t index){
    *map = *map | (1 << index);
}

void reset_bit(uint8_t *map, uint8_t index){
    *map = *map & (~(1 << index));
}

void toggle_bit(uint8_t *map, uint8_t index){
    *map = *map ^ (1 << index);
}

uint8_t get_bit(uint8_t map, uint8_t index){
    return (map & (1 << index)) > 0;
}

char *byte_to_bits(uint8_t byte){
    static char bits[BYTE_TO_BITS + 1] = "\0";

    for(uint8_t i = 0; i < BYTE_TO_BITS; i++, byte >>= 1)
        bits[BYTE_TO_BITS - (i + 1)] = (byte & 1) + '0';
    return bits;
}