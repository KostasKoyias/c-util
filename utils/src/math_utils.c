#include <stdlib.h>

int math_round(float x){
    if(x < 0)
        return (-1) * (((-1) * x + 0.5)/1);
    else
        return (x + 0.5)/1;
}
