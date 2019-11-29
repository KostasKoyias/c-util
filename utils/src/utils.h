#ifndef _utils_H
#define _utils_H

    #include <stdio.h>
    #include <stdint.h>

    // memory-related utilities
    void reset(void *);
    int memswap(void *, void *, size_t);

    // error-related utilities
    int perror_return(const char *, int);
    int error_return(int, const char*, ...);

    // string-related utilities
    int str_rename(char **, const char *);
    int str_count(char *, char);
    int last_index_of(char, const char*);


    // general-purpose utils
    uint64_t rand_bits(uint8_t);
    int math_round(float);
    
#endif