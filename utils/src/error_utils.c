#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

int perror_return(const char *msg, int rv){
    if(msg == NULL)
        return -1;
    perror(msg);
    return rv;
}

int error_return(int ret_val, const char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    return ret_val;
}