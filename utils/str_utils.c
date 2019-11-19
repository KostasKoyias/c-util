#include <stdlib.h>
#include <string.h>
#include "utils.h"

int str_rename(char **dst, const char *src){
    if(dst == NULL || src == NULL)
        return -1;
    
    // if destination does not exits, allocate space for it
    if(*dst == NULL)
        *dst = malloc(strlen(src) + 1);

    //  else if the space previously allocated is not enough, re-allocate
    else if(strlen(*dst) < strlen(src) + 1)
        *dst = realloc(*dst, strlen(src) + 1);

    // copy src to dst
    strcpy(*dst, src);
    return 0;
}