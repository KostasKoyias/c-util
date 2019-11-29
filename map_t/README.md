# README #

**map_t** is a linked hash-map using a vector of buckets, each of them
represented as a doubly linked-list to
store any data-type, primitive or user-defined based on a key field,
adding a new bucket whenever the load factor sur-passes a threshold.

## How it's set ##

To create a map of a certain type you need to define
some 'member methods' of that type as described in the [API.md](./API.md).

## How to use it ##

In order to use a generic map(`map_t`),

* use the [makefile](./src/demo/makefile) included under `src/demo`
* then link the corresponding .o files to your project and finally
* *\#include `map.h`* in all files using a map_t

Before using this library, take a good look at the [API](./API.md).
It's easy to understand and it will help you learn how
to use the library easy and quickly.\

## Let's run it ##

Under `src/demo`, a makefile template and a demo source file, [main.c](./src/demo/main.c)
using the basic API methods
with an example of a [struct person](../list_t/src/demo/person.h) are included.

Type

```bash
map_t >> cd src/demo
map_t/src/demo >> make
map_t/src/demo >> ./main
```

to run the sample.

### Author ###

Name:  Kostas Koyias  
Email: sdi1500071@di.uoa.gr

#### notes ####

1. Insertion on a full map can, if requested, re-allocate space
for a single item instead of doubling the size of the map.
This is not encouraged in most cases.
Use this only if insertions are rare.
