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

int str_count(char *str, char delim){
    int count;
    if(str == NULL)
        return -1;

    count = 0;
    while(str != NULL && *str != '\0'){
        str = strchr(str, delim);
        if(str != NULL){
            count++;
            str++;
        }
    }
    return count;
}

int last_index_of(char c, const char* str){
    int i;
    if(str == NULL)
        return -1;

    for(i = strlen(str)-1; i >= 0 && str[i] != c; i--);
    return i < 0 || str[i] != c ? -1 : i;
}