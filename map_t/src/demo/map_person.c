#include <assert.h>
#include "map_person.h"
#include "person.h"

// person_t member methods are defined below
uint64_t get_key(const void *person){
    const person_t *p = person;
    assert(person);
    return p->id;
}