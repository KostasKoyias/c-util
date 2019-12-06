# matrix_t API

## Methods Summary

### Basic

| Name             | Description                                                                        |
|------------------|----------------------------------------------------------------------------------------------------------------------------------|
| `matrix_init`    | Initialize a matrix defining the number of columns.|
| `matrix_isempty` | Return 1 if matrix is empty or else 0.                                                |
| `matrix_finalize`| Shrink matrix size from bottom-up to fit content. Return the number of rows removed.                                                |
| `matrix_set`     | Insert an element in the matrix specifying the number of row & column. If matrix is empty, initial capacity is set to 4. If the current number of rows is smaller, rows filled with 0s are added as needed.|
| `matrix_get`     | Get element at position (i, j). If (i, j) is out_of_bounds an exception is thrown.                                                |
| `matrix_print`   | Display all numbers in a matrix in a tabular fashion.  |
| `matrix_free`    | Free all resources allocated for this matrix.|
