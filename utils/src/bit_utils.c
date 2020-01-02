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

void set_bit(uint32_t *map, uint8_t index){
    *map = *map | (1 << index);
}

uint8_t get_bit(uint32_t map, uint8_t index){
    return (map & (1 << index)) > 0;
}