# README #

**matrix_t** is a dynamic NxM matrix of 64-bit unsigned integers.

## Insertion ##

On regular insertion, the element will be placed in the next position available.
In case of an empty or full matrix, a new row will be added,
with all values set to 0s.

Inserting an element on a **specified position** `(i, j)`, will result in creating
`i + 1 - matrix.rows` new rows filled with 0s, in case `i >= matrix.rows`.

## How to use it ##

Under `src/demo`, a [makefile](./src/demo/makefile) template
and a demo source file,
[main.c](./src/demo/main.c)
using the basic [API](./API.md) methods are included.

Type

```bash
matrix_t >> cd src/demo
matrix_t/src/demo >> make
matrix_t/src/demo >> ./main
```

to run the sample.

### Author ###

Name:  Kostas Koyias  
Email: sdi1500071@di.uoa.gr
