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

    // initialize vector    
    vector_init(&v, sizeof(person_t), init_wrapper, NULL, cmp, NULL, print, destroy);
    for(int i = 0; i < PEOPLE; i++)
        vector_insert(&v, rand() % MAX_RANK, "John Doe");
    vector_print(&v);

    // quick-sort using cmp & display
    fprintf(stdout, "\n\e[1;4mSorting by rank(asc)...\e[0m\n");
    vector_qsort(&v);
    vector_print(&v);

    fprintf(stdout, "\n\e[1;4mReversing items...\e[0m\n");
    vector_reverse(&v);
    vector_print(&v);

    vector_free(&v);
    return 0;
}