#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include "vector.h"
#include "heap.h"
#include "utils.h"

#define SIZE 10
#define MAX 100
#define SHIFT 5

// array member methods for specific type
int comparator(const void *, const void *);

// print an array of integers
int print(const int *array, int n){
    assert(array);

    putchar('[');
    for(int i = 0; i < n-1; i++)
        printf("%d, ", array[i]);
    printf("%d]\n", array[n-1]);

    return 0;
}

/*
 * testing sorting methods, comparing qsort to heap-sort and merge-sort
 * for a random set of integers in a pre-defined range
 */  
int main(){
    int heap[SIZE], mrg[SIZE], array[SIZE], heap_works, mrg_works, seed;

    // initialize arrays
    seed = getpid() << SHIFT;
    srand(seed);
    for(int i = 0; i < SIZE; i++)
        array[i] = mrg[i] = heap[i] = rand() % MAX;

    // display initial array
    print(array, SIZE);

    // sort using different methods
    qsort(array, SIZE, sizeof(int), comparator); // stdlib.qsort
    hsort(heap, SIZE, sizeof(int), comparator);  // heap_t.src.main.hsort
    msort(mrg, SIZE, sizeof(int), comparator);   // utils.src.msort 

    // display outcome of each method
    print(array, SIZE);
    print(heap, SIZE);
    print(mrg, SIZE);

    // compare stdlib.qsort to hsort & msort
    mrg_works = (memcmp(array, mrg, SIZE * sizeof(int)) == 0);
    heap_works = (memcmp(array, heap, SIZE * sizeof(int)) == 0);
    fprintf(stdout, "%s%s\n", heap_works && mrg_works ? "\e[1;32mSuccess" : "\e[1;31mFailure", "\e[0m");

    return 0;
}

// integer comparator matching qsort prototype
int comparator(const void *a, const void *b){
    assert(a && b);
    return (*(int*)a) - (*(int*)b);
}