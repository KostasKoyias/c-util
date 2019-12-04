#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

int str_rename(char **dst, const char *src){
    assert(dst && src);
    
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
    assert(str);

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
    assert(str);

    for(i = strlen(str)-1; i >= 0 && str[i] != c; i--);
    return i < 0 || str[i] != c ? -1 : i;
}

// for each matching part shift initial string to the left as many positions as the length of the substring
int remove_all(char *str, char *sub){
    assert(str && sub && strlen(str) >= strlen(sub));

    for(int i = 0; i < strlen(str)- strlen(sub) + 1; i++){
        while(memcmp(str + i, sub, strlen(sub)) == 0 && strlen(str) >= strlen(sub))
            memmove(str + i, str + i + strlen(sub), strlen(str + i + strlen(sub)) + 1);
    }

    return 0;
}

int count_matches(char* str, const char *pattern){
    int i, matches = 0;
    size_t len1, len2;
    assert(str && pattern);
    if((len1 = strlen(str)) < 1 || (len2 = strlen(pattern)) < 1)
        return 0;

    for(i = matches = 0; i < len1 - len2 + 1; i++){
        if(memcmp(str + i, pattern, len2) == 0){
            matches++;
            i += len2-1;
        }
    }
    return matches;
}

// surround all parts of str that match a pattern with strings s1 & s2, returns a pointer to the re-allocated space
char *surround_with(char *str, const char *pattern, const char *s1, const char *s2){
    int i, count, occ;
    size_t len1, len2, replace_len = strlen(s1) + strlen(s2), total_len;
    assert(str && pattern && s1 && s2);
    
    if((len2 = strlen(pattern)) < 1 || (len1 = strlen(str)) < len2)
        return NULL;

    // count the number of occurrences of the pattern inside the string
    if((occ = count_matches(str, pattern)) == 0)
        return str;

    // estimate the total length based on the number of matches
    total_len = replace_len * occ + len1;

    // re-allocate & initialize the appropriate amount of space to fit the color codes
    str = realloc(str, total_len + 1);
    bzero(str + len1, total_len + 1 - len1);

    for(i = count = 0; i < total_len - len2; i++){

        // for each pattern match found
        if(memcmp(str + i, pattern, len2) == 0){

                // move the rest of the string to the right
                memmove(str + i + len2 + replace_len, str + i + len2, len1 - (i + len2 - replace_len * count));

                // wrap around the matched part using the color codes
                memcpy(str + i, s1, strlen(s1));
                memcpy(str + i + strlen(s1), pattern, strlen(pattern));
                memcpy(str + i + strlen(s1) + strlen(pattern), s2, strlen(s2));

                i += len2 + replace_len - 1;
                count++;
        }
    }
    return str;
}