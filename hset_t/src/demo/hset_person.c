#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hset_person.h"
#include "person.h"

int init_wrapper_with_id(void *person, va_list props){
    uint64_t id = va_arg(props, uint64_t);
    char *name = va_arg(props, char*);
    person_t *p = person;
    assert(p && name);

    p->id = id;
    p->name = malloc(strlen(name) + 1);
    strcpy(p->name, name);
    return 0;
}

// a copy constructor is required for the hset to work
int clone(void *dst, va_list props){
    person_t *p1 = dst, *p2 = (person_t*)va_arg(props, void *);
    assert(dst);

    p1->id = p2->id;
    p1->name = malloc(strlen(p2->name) + 1);
    strcpy(p1->name, p2->name);
    return 0;    
}

// person_t member methods are defined below
uint64_t get_key(const void *person){
    const person_t *p = person;
    assert(person);
    return p->id;
}