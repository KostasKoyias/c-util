/*
 * add some methods to the person_t example of list_t demo, suitable for the set_t demo
 */ 

#ifndef _set_person_H
#define _set_person_H
    #include <stdint.h>
    #include "person.h"

    int init_wrapper_with_id(void *, va_list);
    int clone(void *, va_list);
    uint64_t get_key(const void *);
#endif