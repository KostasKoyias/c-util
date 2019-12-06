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

// add rows to a matrix, filled with -1s indicating empty spots
void matrix_resize(void *matrix, int64_t rows){
    uint64_t i;
    matrix_t *m = matrix;
    assert(matrix);

    // if this is a shrinking
    if(rows < 0){
        for(uint64_t i = m->rows + rows; i < m->rows; i++)
            reset(m->data[i]);
    }

    // update matrix
    m->rows += rows;
    m->data = realloc(m->data, m->rows * sizeof(uint64_t*));

    // fill added rows with -1s
    for(i = m->rows - rows; i < m->rows; i++){
        m->data[i] = malloc(m->cols * sizeof(uint64_t));
        memset(m->data[i], UINT32_MAX, m->cols * sizeof(uint64_t));
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
        matrix_resize(matrix, MATRIX_INITIAL_CAPACITY);
    else if(capacity_required > m->rows) // double the # of rows, if there aren't enough
        matrix_resize(matrix, capacity_required - m->rows);

    m->data[row][col] = value;
    return 0;
}

uint64_t matrix_get(void *matrix, uint64_t i, uint64_t j){
    matrix_t *m = matrix;
    assert(matrix && i < m->rows && j < m->cols);
    return m->data[i][j];
}

int matrix_empty_row(void *matrix, uint64_t row){
    int i;
    matrix_t *m = matrix;
    assert(matrix);

    if(row >= m->rows)
        return -1;
    
    for(i = 0; i < m->cols && m->data[row][i] == UINT64_MAX; i++);
    return i == m->cols;
}

uint64_t matrix_finalize(void *matrix){
    matrix_t *m = matrix;
    uint64_t i;
    assert(matrix);

    // release consecutive bottom-most empty rows
    for(i = m->rows-1; i >= 0 && matrix_empty_row(matrix, i); i--);
    if(i < m->rows - 1)
        matrix_resize(matrix, i + 1 - m->rows);

    return m->rows - (i + 1); // the number of rows released
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
            fprintf(stdout, "%-23ld\t", m->data[i][j]);
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
