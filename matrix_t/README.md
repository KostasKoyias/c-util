# README #

**matrix_t** is a dynamic NxM matrix of 64-bit unsigned integers.

## Insertion ##

Inserting an element on a **specified position** `(i, j)` where `i > matrix.rows`
will result in increasing the number of rows to the smallest power of 2 `x`
where `x > i`.

For example, suppose that matrix.rows equals 16 and an insertion
at (78, 3) is requested. Then matrix.rows is set to 128 and
the appropriate space reallocation takes place.

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
