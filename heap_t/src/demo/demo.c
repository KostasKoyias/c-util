#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "utils.h"
#include "heap.h"
#include "integer.h"

#define SIZE 6
#define MAX 100
#define ITEMS 3

/*
 * testing sorting methods, comparing qsort to heap-sort and merge-sort
 * for a random set of integers in a pre-defined range
 */  
int main(){
    int array[SIZE], items[ITEMS] = {1, MAX, (int)MAX/2};
    heap_t pqueue;

    // initialize two identical arrays
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++)
        array[i] = rand() % MAX;

    // display initial array
    fprintf(stdout, "\e[1;4m > Initial array\n\e[0m");
    print(array, SIZE);

    // create a heap out of the array
    fprintf(stdout, "\n\e[1;4m > Into a max heap\n\e[0m");
    heap_init(&pqueue, array, SIZE, sizeof(int), DEEP, init, comparator, NULL);
    print(pqueue.array, SIZE);

    // display the root item
    fprintf(stdout, "\n\e[1;4m > Highest priority item: %d\n\e[0m", *((int*)heap_best(&pqueue)));

    // adding a large, a small and a middle item
    fprintf(stdout, "\n\e[1;4m > Inserting items\n\e[0m");
    for(int i = 0; i < ITEMS; i++){
        heap_push(&pqueue, items + i);
        print(pqueue.array, SIZE + i + 1);
    }

    // pop items until empty
    fprintf(stdout, "\n\e[1;4m > Pop max until empty\n\e[0m");
    for(int i = 0; !heap_isempty(&pqueue); i++){
        print(pqueue.array, SIZE + ITEMS - i);
        heap_pop(&pqueue);
    }

    // let go of memory allocated
    heap_free(&pqueue);
    return 0;
}