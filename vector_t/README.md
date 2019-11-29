# README #

**vector_t** is a dynamic one-dimensional array,
doubling it's size on insertion<sup style="font-weight: bolder;color: #1d9fcb">[1](###notes)</sup>
if full, therefore having constant amortized insertion complexity.

## How it's set ##

To create a vector of a certain type you need to define
some 'member methods' of the particular type a vector cell will point to.
After that, you can create a vector of this type and apply
whatever function(e.g vector_insert, vector_reduce etc.) on it.

## How to use it ##

In order to use a generic vector(`vector_t`) in one of your programs,

* first compile

  * vector.c
  * vector_utils.c and
  * utils.c

* then link the corresponding .o files to your project and finally
* *\#include `vector.h`* in all files using a vector_t.

Before using this library, take a good look at the [API](./API.md).
It's easy to understand and it will help you learn how
to use the library easy and quickly.\

## Let's run it ##

To make things easier, a makefile template and two demo source files, [main.c](./src/demo/main.c)
using the basic API methods and [order.c](./src/demo/order.c) using some of the more advanced API
using an example of a struct person are included under `src/demo`

Type

```bash
vector_t >> cd src/demo
vector_t/src/demo >> make
vector_t/src/demo >> ./main
vector_t/src/demo >> ./order
```

to run the sample.

### Author ###

Name:  Kostas Koyias  
Email: sdi1500071@di.uoa.gr

### Notes ###

1. Insertion on a full vector can, if requested, re-allocate space
for a single item instead of doubling the size of the vector.
This is not encouraged in most cases.
Use this only if insertions are rare.
