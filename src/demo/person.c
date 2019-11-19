#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "person.h"

// person_t member methods are defined below
int compare(const void *p1, const void *vid){
    assert(p1 != NULL && vid != NULL);

    const person_t *pp1 = p1;
    const int *id = vid;
    return pp1->id - *id;
}

int init(void *p1, const void *p2){
    assert(p1 != NULL && p2 != NULL);

    person_t *pp1 = (person_t*)p1, *pp2 = (person_t *)p2;
    pp1->id = pp2->id;
    strcpy(pp1->name, pp2->name);
    return 0;
}

int print(const void *p1){
    assert(p1 != NULL);

    const person_t *pp1 = (person_t*)p1;
    fprintf(stdout, "\nId: %d\nName: %s\n", pp1->id, pp1->name);
    return 0;
}

int sum_ids(void *data, int total){
    person_t *p = data;
    assert(data != NULL);

    return p->id + total;
}

int prod_ids(void *data, int total){
    person_t *p = data;
    assert(data != NULL);

    return p->id * total;
}