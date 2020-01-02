#include <stdio.h>
#include <time.h>
#include "matrix.h"
#define MAX 1000
#define COLUMNS 5

int main(){
    matrix_t matrix;

    srand(time(NULL));
    matrix_init(&matrix, COLUMNS);
    
    // insert item at a specified position
    for(uint64_t i = 0; i < COLUMNS; i++){
        matrix_set(&matrix, rand() % MAX + 1, i, i);
        matrix_set(&matrix, rand() % MAX + 1, COLUMNS-1-i, i);
    }

    matrix_print(&matrix);
    matrix_finalize(&matrix); // shrink to fit content
    matrix_print(&matrix);
    fprintf(stdout, "Last value: %lu\n", matrix.data[matrix.rows-1][matrix.cols-1]);

    matrix_free(&matrix);
}