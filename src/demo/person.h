#ifndef _person_H
#define _person_H
    #include <stdarg.h>
    #define MAX_NAME 20


    typedef struct person{
        unsigned int id;
        char name[MAX_NAME];
    }person_t;

    int compare(const void*, const void*);
    int init_wrapper(void *, va_list);
    int init(void*, const void*);
    int print(const void*);
    void destroy(void *);
    int sum_ids(void*, int);
    int prod_ids(void*, int);

#endif