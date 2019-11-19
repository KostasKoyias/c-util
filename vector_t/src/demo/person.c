#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "person.h"

// unpack arguments and pass them to the constructor
int init_wrapper(void *person, va_list props){
    int rank;
    char *name;
    person_t *this = person;
    assert(person);

    // get arguments from props list
    rank = va_arg(props, int);
    name = va_arg(props, char*);
    return init(this, rank, name);
}

int init(void *person, int rank, char *name){
    static int id = 0; // auto-increment
    person_t *this = person;
    assert(person && name);

    // initialize this person
    this->id = id++; // auto-increment
    this->rank = rank;

    this->name = malloc(strlen(name) + 1);
    strcpy(this->name, name);
    return 0;
}

// initialize a person from another
void clone(void *a, const void *b){
    person_t *pa = a;
    const person_t *pb = b;
    assert(a && b);

    pa->id = pb->id;
    pa->rank = pb->rank;
    if(pb->name != NULL){
        pa->name = malloc(strlen(pb->name) + 1);
        strcpy(pa->name, pb->name);
    }
}

// compare a pair of people by their id, or whatever you wish really
int seek(const void *a, const void *id){
    const person_t *pa = a;
    const int *unique_identifier = id; 
    assert(a && id);
    return pa->id == *unique_identifier;
}

// compare a pair of people by their id, or whatever you wish really
int cmp(const void *a, const void *b){
    const person_t *pa = a, *pb = b; 
    assert(a && b);
    return pa->rank - pb->rank;
}

void print(void *person){
    const person_t *this = person;
    assert(person);
    fprintf(stdout, "Id: %d\nRank: %d\nName: %s\n\n", this->id, this->rank, this->name);
}

void destroy(void *person){
    person_t *this = person;
    assert(person);
    free(this->name);
}

void sum_reducer(void *total, void *person){
    int *t = total;
    assert(total && person);
    *t += ((person_t*)person)->id;
}

void prod_reducer(void *total, void *person){
    int *t = total;
    assert(total && person);
    *t *= ((person_t*)person)->rank;
}