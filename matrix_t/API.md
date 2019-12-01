# matrix_t API

## Methods Summary

### Basic

| Name             | Description                                                                        |
|------------------|----------------------------------------------------------------------------------------------------------------------------------|
| `matrix_init`    | Initialize a matrix defining the number of columns.|
| `matrix_insert`  | Insert an 64-bit unsigned integer in the next empty position. A single row is added before the insertion in case the matrix is either empty or full.|
| `matrix_isempty` | Return 1 if matrix is empty or else 0.                                                |
| `matrix_isfull`  | Return 1 if matrix is full or else 0.                                                |
| `matrix_set`     | Insert an element in the matrix specifying the number of row & column. If the current number of rows is smaller, rows filled with 0s are added as needed.|
| `matrix_print`   | Display all numbers in a matrix in a tabular fashion.  |
| `matrix_free`    | Free all resources allocated for this matrix.|
