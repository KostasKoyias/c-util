#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "person.h"

// person_t member methods are defined below
int compare(const void *p1, const void *vid){
    assert(p1 && vid);

    const person_t *pp1 = p1;
    const int *id = vid;
    return pp1->id - *id;
}

int init_wrapper(void *p, va_list props){
    char *name;
    assert(p);
    name = va_arg(props, char*);
    return init(p, name);
}

int init(void *person, const void *name){
    static unsigned int id = 1;
    person_t *p = person;
    assert(person && name);

    p->id = id;
    p->name = malloc(strlen(name) + 1);
    strcpy(p->name, name);

    id += 11; // for the next person
    return 0;
}

int print(const void *p1){
    const person_t *pp1 = (person_t*)p1;
    assert(p1);

    fprintf(stdout, "\nId: %d\nName: %s\n", pp1->id, pp1->name);
    return 0;
}

void destroy(void *person){
    person_t *p = person;
    assert(person);
    free(p->name);
}

int sum_ids(void *data, int total){
    person_t *p = data;
    assert(data);

    return p->id + total;
}

int prod_ids(void *data, int total){
    person_t *p = data;
    assert(data);

    return p->id * total;
}