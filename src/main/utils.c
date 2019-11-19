#include "include/utils.h"

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

// free all memory pointed by a some pointer & set it back to NULL
int reset(void *ptr){
    if(ptr == NULL)
        return -1;
    free(ptr);
    ptr = NULL;
    return 0;
}

int perror_return(const char *msg, int rv){
    if(msg == NULL)
        return -1;
    perror(msg);
    return rv;
}