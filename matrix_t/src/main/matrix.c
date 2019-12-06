#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"
#include "utils.h"

int matrix_init(void *matrix, uint64_t cols){
    matrix_t *m = matrix;
    assert(matrix);

    m->data = NULL;
    m->rows = 0;
    m->cols = cols;
    return 0;
}

// add rows to a matrix, filled with 0s
void matrix_expand(void *matrix, uint64_t rows){
    uint64_t i;
    matrix_t *m = matrix;
    assert(matrix);
    m->rows += rows;
    m->data = realloc(m->data, m->rows * sizeof(uint64_t*));

    for(i = m->rows - rows; i < m->rows; i++){
        m->data[i] = malloc(m->cols * sizeof(uint64_t));
        memset(m->data[i], 0, m->cols * sizeof(uint64_t));
    }
}

int matrix_set(void *matrix, uint64_t value, uint64_t row, uint64_t col){
    matrix_t *m = matrix;
    uint64_t capacity_required;
    uint8_t bits = 64;
    assert(matrix);
    if(col > m->cols-1)
        return -1;

    capacity_required = nearest_power_of2(row + 1, bits);
    if(m->rows == 0) // if matrix is empty
        matrix_expand(matrix, MATRIX_INITIAL_CAPACITY);
    else if(capacity_required > m->rows) // double the # of rows, if there aren't enough
        matrix_expand(matrix, capacity_required - m->rows);

    m->data[row][col] = value;
    return 0;
}

void matrix_print(void *matrix){
    uint64_t i, j;
    matrix_t *m = matrix;
    assert(matrix);

    fprintf(stdout, 
            "\e[1;4mMatrix\e[0m\n * rows: %lu\n * cols: %lu\n * content\n", 
            m->rows, m->cols);
    for(i = 0; i < m->rows; i++){
        for(j = 0; j < m->cols; j++)
            fprintf(stdout, "%-23lu\t", m->data[i][j]);
        fputc('\n', stdout);
    }
}

void matrix_free(void *matrix){
    uint64_t i;
    matrix_t *m = matrix;
    assert(matrix);

    for(i = 0; i < m->rows; i++)
        reset(m->data[i]);
    reset(m->data);
}

int matrix_isempty(void *matrix){
    matrix_t *m = matrix;
    assert(matrix);
    return m->rows == 0;
}
