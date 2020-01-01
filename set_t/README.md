# README #

**hset_t** is a linked hash-set using a vector of buckets, each of them
represented as a doubly linked-list to
store any data-type, primitive or user-defined based on a key field,
adding a new bucket whenever the load factor
sur-passes a threshold([linear hashing](http://cgi.di.uoa.gr/~ad/M149/e_ds_linearhashing.pdf)).

## How it's set ##

To create a set of a certain type you need to define
some 'member methods' of that type as described in the [API.md](./API.md).

## How to use it ##

In order to use a generic set(`hset_t`),

* use the [makefile](./src/demo/makefile) included under `src/demo`
* then link the corresponding .o files to your project and finally
* *\#include `set.h`* in all files using a hset_t

Before using this library, take a good look at the [API](./API.md).
It's easy to understand and it will help you learn how
to use the library easy and quickly.

## Let's run it ##

Under `src/demo`, a makefile template and a demo source file, [main.c](./src/demo/main.c)
using the basic API methods
with an example of a [struct person](../list_t/src/demo/person.h) are included.

Type

```bash
hset_t >> cd src/demo
hset_t/src/demo >> make
hset_t/src/demo >> ./main
```

to run the sample.

Other than that, the demo folder contains an evaluation test of
the hash function as well, applying
the [chi-squared test](https://en.wikipedia.org/wiki/Chi-squared_test).

### Author ###

Name:  Kostas Koyias  
Email: sdi1500071@di.uoa.gr
