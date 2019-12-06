#include <stdio.h>
#include "utils.h"
#define NUMS 8
#define BITS 32
#define FLOATS 5

int main(){
    float nums[FLOATS] = {1.51, 2.49, 4.99, 9.0, 16.3};

    for(int i = 1; i < NUMS + 1; i++)
        fprintf(stdout, "\e[1;4m%d\e[0m\n * Is Power of 2: %s\n * Next Power of 2: %d\n",
                i * i, is_power_of2(i * i) ? "true" : "false", nearest_power_of2(i * i, BITS));

    fprintf(stdout, "\n\e[1;4mRounding floats\e[0m\n");
    for(int i = 0; i < FLOATS; i++)
        fprintf(stdout, " >> || %.2f || = %d\n", nums[i],  math_round(nums[i]));

    return 0;
}   