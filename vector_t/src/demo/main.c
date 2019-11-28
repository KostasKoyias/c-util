#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "vector.h"
#include "person.h"
#include "utils.h"
#define PEOPLE 5
#define MAX_RANK 20

int main(){
    srand(time(NULL));
    vector_t v;
    int id, start;
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};

    // initialize vector providing member methods for type 'person_t', not all of them are mandatory   
    vector_init(&v, sizeof(person_t), init_wrapper, seek, cmp, clone, print, destroy);
    for(int i = 0; i < PEOPLE; i++)
        vector_insert(&v, 0, rand() % MAX_RANK, names[i]);
    vector_print(&v);
    fprintf(stdout, "-------------------\n");

    // get by index
    printf("\e[1;4mElement at position 0\e[0m\n");
    print(vector_get(&v, 0));
    printf("\e[1;4mElement at position %d\e[0m\n", PEOPLE-1);
    print(vector_get(&v, PEOPLE-1));

    // get by id using seek
    id = 2;
    printf("\e[1;4mElement with id equal to %d\e[0m\n", id);
    print(vector_seek(&v, &id, NULL));

    start = 0;
    vector_reduce(&v, &start, sum_reducer);
    fprintf(stdout, "\e[1;4mSum of ids\e[0m: %d\n", start);

    start = 1;
    vector_reduce(&v, &start, prod_reducer);
    fprintf(stdout, "\e[1;4mProd of ranks\e[0m: %d\n", start);

    printf("\e[1;4mRemoving elements\e[0m at position 0, the one with id equal to %d and the last one\n", id);
    vector_remove(&v, 0);
    vector_delete(&v, &id);
    vector_remove(&v, v.next-1);
    vector_print(&v);

    printf("\e[1;4mReducing vector's capacity to fit size actually needed\n\e[0m");
    vector_shrink(&v);
    vector_print(&v);

    vector_free(&v);
    return 0;
}