#include <time.h>
#include "matrix.h"
#define MAX 1000
#define COLUMNS 5
#define NUMS 12

int main(){
    matrix_t matrix;

    srand(time(NULL));
    matrix_init(&matrix, COLUMNS);
    
    // insert items in the next available position
    for(uint64_t i = 0; i < NUMS; i++)
        matrix_insert(&matrix, rand() % MAX + 1);

    // insert an item at a specified position (row, col)
    matrix_set(&matrix, rand() % MAX + 1, NUMS/COLUMNS + 3, COLUMNS/2);

    matrix_print(&matrix);
    matrix_free(&matrix);
}