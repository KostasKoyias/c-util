#ifndef _utils_H
#define _utils_H

    #include <stdio.h>
    #include <stdint.h>
    #define BYTE_TO_BITS 8

    // memory-related utilities
    void reset(void *);
    int memswap(void *, void *, size_t);

    // error-related utilities
    int perror_return(const char *, int);
    int error_return(int, const char*, ...);

    // string-related utilities
    int str_rename(char **, const char *);
    int str_count(char *, char);
    char* str_reverse(char *);
    int last_index_of(char, const char*);
    int count_matches(char* , const char *);
    int remove_all(char* , char *);
    char* surround_with(char* , const char *, const char *, const char *);

    // array sorting methods
    void msort(void *, size_t, size_t, int (*)(const void *, const void *));
    void hsort(void *, size_t, size_t, int (*)(const void *, const void *));

    // bit-by-bit utilities
    uint64_t rand_bits(uint8_t);
    void set_bit(uint8_t *, uint8_t);
    void reset_bit(uint8_t *, uint8_t);
    void toggle_bit(uint8_t *, uint8_t);
    uint8_t get_bit(uint8_t, uint8_t);
    char *byte_to_bits(uint8_t);

    // math utilities
    int math_round(float);
    int is_power_of2(uint64_t);
    uint64_t nearest_power_of2(uint64_t, uint8_t);

    
#endif