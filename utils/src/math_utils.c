#include "utils.h"

int math_round(float x){
    if(x < 0)
        return (-1) * (((-1) * x + 0.5)/1);
    else
        return (x + 0.5)/1;
}

// if a single bit is set, then num-1 and num, have no overlapping bits set
int is_power_of2(uint64_t num){
    return ((num - 1) & num) == 0;
}

int nearest_power_of2(uint64_t num, uint8_t bits){
    uint8_t max_bit = bits + 1;

    // if this is a power of 2, return as is
    if(is_power_of2(num))
        return num;

    // else look for the leftmost bit set
    for(uint8_t i = 0; i < bits; i++, num >>= 1)
        if(num % 2)
            max_bit = i;

    // if num == 0 return 1
    if(max_bit == bits + 1)
        return 1;
    // else set the next of the leftmost bit set(e.g 0[1]10 -> [1]000)
    else
        return 1 << (max_bit + 1);

}