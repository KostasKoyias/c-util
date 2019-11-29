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

int math_round(float x){
    if(x < 0)
        return (-1) * (((-1) * x + 0.5)/1);
    else
        return (x + 0.5)/1;
}
