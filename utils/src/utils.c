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