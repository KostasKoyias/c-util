#ifndef _person_H
#define _person_H
    #include <stdarg.h>

    typedef struct person{
        unsigned int id;
        char * name;
    }person_t;

    int seek(const void*, const void*);
    int cmp(const void*, const void*);
    int init_wrapper(void *, va_list);
    int init(void*, const void*);
    void print(void*);
    void destroy(void *);
    int sum_ids(void*, int);
    int prod_ids(void*, int);

#endif