#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "vector.h"
#include "person.h"
#include "utils.h"
#define PEOPLE 5
#define MAX_RANK 100

int main(){
    srand(time(NULL));
    vector_t v;
    int id, start;

    // initialize vector providing member methods for type 'person_t', not all of them are mandatory   
    vector_init(&v, sizeof(person_t), init_wrapper, seek, cmp, clone, print, destroy);
    for(int i = 0; i < PEOPLE; i++)
        vector_insert(&v, rand() % MAX_RANK, "John Doe");
    vector_print(&v);
    fprintf(stdout, "-------------------\n");

    // get by index
    print(vector_get(&v, 0));
    print(vector_get(&v, PEOPLE-1));

    // get by id using seek
    id = 3;
    print(vector_seek(&v, &id));

    // quick-sort using cmp & display
    fprintf(stdout, "Sorting by rank(asc)...\n");
    vector_qsort(&v);
    vector_print(&v);

    start = 0;
    vector_reduce(&v, &start, sum_reducer);
    fprintf(stdout, "Sum of ids: %d\n", start);

    start = 1;
    vector_reduce(&v, &start, prod_reducer);
    fprintf(stdout, "Prod of ranks: %d\n", start);

    vector_free(&v);
    return 0;
}