#include <stdio.h>
#include <assert.h>
#include "integer.h"
#include "string.h"

// integer comparator matching qsort and heap_sort prototype
int comparator(const void *a, const void *b){
    assert(a && b);
    return (*(int*)a) - (*(int*)b);
}

// print an array of integers
int print(const int *array, int n){
    assert(array);

    putchar('[');
    for(int i = 0; i < n-1; i++)
        printf("%d, ", array[i]);
    printf("%d]\n", array[n-1]);

    return 0;
}

// initialize an integer array cell, matching vector.init prototype method(required)
int init(void *integer, va_list props){
    int *i;
    assert(integer);
    i = va_arg(props, int*);
    memcpy(integer, i, sizeof(int));
    return 0;
}