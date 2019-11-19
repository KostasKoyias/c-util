#ifndef _person_H
#define _person_H

    #include <stdarg.h>
    #define MAX_NAME 20

    typedef struct person{
        int id;
        int rank;
        char *name;
    }person_t;

    int init_wrapper(void *, va_list);
    int init(void *, int, char*);
    int seek(const void *, const void*);
    int cmp(const void *, const void*);
    void clone(void *, const void*);
    void print(void *);
    void destroy(void *);
    void sum_reducer(void *, void*);
    void prod_reducer(void *, void*);

#endif