#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int perror_return(const char *msg, int rv){
    if(msg == NULL)
        return -1;
    perror(msg);
    return rv;
}