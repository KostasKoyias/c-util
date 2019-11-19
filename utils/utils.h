#ifndef _utils_H
#define _utils_H

    #include <stdio.h>

    // memory-related utilities
    void reset(void *);
    int memswap(void *, void *, size_t);

    // error-related utilities
    int perror_return(const char *, int);

    // string-related utilities
    int str_rename(char **, const char *);
    
#endif