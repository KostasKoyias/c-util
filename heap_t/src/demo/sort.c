#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "integer.h"
#include "utils.h"
#include "heap.h"

#define SIZE 20
#define MAX 100

/*
 * testing sorting methods, comparing qsort to heap-sort and merge-sort
 * for a random set of integers in a pre-defined range
 */  
int main(){
    int array0[SIZE], array1[SIZE], works;

    // initialize two identical arrays
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++)
        array0[i] = array1[i] = rand() % MAX;

    // display initial array
    print(array0, SIZE);

    // sort each array with a different method
    qsort(array0, SIZE, sizeof(int), comparator);
    hsort(array1, SIZE, sizeof(int), comparator);

    // print result of heap-sort
    print(array1, SIZE);

    // compare stdlib.qsort to hsort
    works = (memcmp(array0, array1, SIZE * sizeof(int)) == 0);
    fprintf(stdout, "%s%s\n", works ? "\e[1;32mSuccess" : "\e[1;31mFailure", "\e[0m");

    return 0;
}