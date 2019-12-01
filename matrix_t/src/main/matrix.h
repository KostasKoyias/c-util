#ifndef matrix_H_
#define matrix_H_                           

    #include <stdlib.h>
    #include <stdint.h>
    #include <stdarg.h>
    #define DEFAULT_NAME "No name list"

    typedef struct matrix{
        uint64_t **data;
        uint64_t rows;
        uint64_t next; // next available position in last row
        uint64_t cols;
    }matrix_t;

    int matrix_init(void *, uint64_t);
    void matrix_insert(void *, uint64_t);
    void matrix_set(void *, uint64_t, uint64_t, uint64_t);
    void matrix_expand(void*, uint64_t);
    void matrix_print(void*);
    void matrix_free(void*);
    int matrix_isempty(void *);
    int matrix_isfull(void *);

#endif