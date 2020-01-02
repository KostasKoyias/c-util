# c-util #

## Intro ##

This project aims at making coding in C a little easier,
by providing some vital **generic** data structures, as well as
some utility functions.

## Data Structures ##

All data structures provided are **dynamic**, allocating space in the heap
for their content and letting go of that space on node deletion
or overall structure destruction. They also require some member methods
fit to the specific data type they are requested to host, in order to be able
to appropriately initialize, display and destroy an instance created.

### list_t ###

This structure is a doubly linked-list allowing insertion on both ends
and deletion from the beginning or by value, therefore operating
both as a queue and as a stack.\
Please take a look at the corresponding
documentation for the [implementation](./list_t/README.md)
and the [API](./list_t/API.md)  to find out more.

### vector_t ###

This structure is a dynamic one-dimensional array, doubling it's size on insertion
if full, therefore having constant amortized insertion complexity.\
Please take a look at the corresponding
documentation for the [implementation](./vector_t/README.md)
and the [API](./vector_t/API.md)  to find out more.

### matrix_t ###

A simple 2D dynamic table of unsigned 64-bit integers,
adding rows as needed on insertion.

### set_t ###

A linked hash-set implemented as a vector of doubly linked-lists,
that can store any data-type, primitive or user-defined,
based on a key field, using
[linear hashing](http://cgi.di.uoa.gr/~ad/M149/e_ds_linearhashing.pdf)
in order to preserve load factor under a certain threshold at all times.

## Utilities ##

Under `./utils/src` one can find many utility functions related to

* memory management
* string manipulation
* bit manipulation
* sorting methods
* error handling and
* mathematics

## How to use it ##

All of the above go with a demo directory or source file
displaying their usage & functionality, as well as
a makefile making compilation & linking easier.
See the corresponding READMEs for more information.

### Last note ###

Data structures mentioned above make use
of the utilities library. Therefore, they all are connected
to this library and can not be used independently.

### About the author ###

* **name**: Kostas Koyias
* **web-page**: [kostaskoyias.github.io](https://kostaskoyias.github.io/)

Thank you.
