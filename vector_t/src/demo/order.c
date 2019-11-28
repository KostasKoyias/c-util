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
    vector_t v;
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};
    int rank;

    srand(time(NULL));

    // initialize vector    
    vector_init(&v, 0, sizeof(person_t), init_wrapper, NULL, cmp, NULL, print, destroy);
    for(int i = 0; i < PEOPLE; i++)
        vector_insert(&v, 0, rank = rand() % MAX_RANK, names[i]);
    vector_print(&v);

    // quick-sort using cmp & display
    fprintf(stdout, "\n\e[1m>> Sorting with `cmp` by rank(asc)...\e[0m\n");
    vector_qsort(&v);
    vector_print(&v);

    fprintf(stdout, "\n\e[1;4m>> Applying binary search for rank %d with `cmp`...\e[0m\n", rank);
    print(vector_bsearch(&v, rank, ""));

    fprintf(stdout, "\n\e[1m>> Reversing items with `cmp`...\e[0m\n");
    vector_reverse(&v);
    vector_print(&v);

    vector_free(&v);
    return 0;
}