#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"
#include "utils.h"

int matrix_init(void *matrix, uint64_t cols){
    matrix_t *m = matrix;
    assert(matrix);

    m->data = NULL;
    m->rows = m->next = 0;
    m->cols = cols;
    return 0;
}

// add rows to a matrix, filled with 0s
void matrix_expand(void *matrix, uint64_t rows){
    uint64_t i;
    matrix_t *m = matrix;
    assert(matrix);
    m->rows += rows;
    m->next = 0;
    m->data = realloc(m->data, m->rows * sizeof(uint64_t*));

    for(i = m->rows - rows; i < m->rows; i++){
        m->data[i] = malloc(m->cols * sizeof(uint64_t));
        memset(m->data[i], 0, m->cols * sizeof(uint64_t));
    }
}

int matrix_set(void *matrix, uint64_t value, uint64_t row, uint64_t col){
    matrix_t *m = matrix;
    assert(matrix);
    if(col > m->cols-1)
        return -1;

    if(row > m->rows){
        matrix_expand(matrix, row + 1 - m->rows);
        m->next = col + 1;
    }
    m->data[row][col] = value;
    return 0;
}

void matrix_insert(void *matrix, uint64_t value){
    matrix_t *m = matrix;
    assert(matrix);

    // insert a new row when in case the matrix is empty or the very last row is full
    if(matrix_isempty(matrix) || matrix_isfull(matrix))
        matrix_expand(matrix, 1);
    m->data[m->rows-1][m->next++] = value;
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

int matrix_isfull(void *matrix){
    matrix_t *m = matrix;
    assert(matrix);
    return m->next == m->cols;
}