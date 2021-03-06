# README #

Using linked lists of various data types for a long time,
implementing a generic doubly linked list that can operate
both as a queue and as a stack in C was probably a good idea.
The interface can be found in `list.h`.

## How it's set ##

To create a doubly linked list of a certain type you need to define
some 'member methods' of the particular type a list node will point to.
After that, you can create a list of this type and apply
whatever function(e.g list_insert, list_reverse etc.) on it.

## How to use it ##

In order to use a generic list(`list_t`) in one of your programs,

* first compile using the [makefile](./src/demo/makefile) provided

* then link the corresponding .o files to your project and finally
* *\#include `list.h` and `utils.h`* in all files using a list_t.

Before using this library, take a good look at the [API](./API.md).
It's easy to understand and it will help you learn how
to use the library easy and quickly.\

## Let's run it ##

To make things easier, a makefile template and a demo c source file called `main.c`
demonstrating how to use the list library, using an example of a struct person
implementation are included under `src/demo`.\
Type

```bash
list_t >> cd src/demo
list_t/src/demo >> make
list_t/src/demo >> ./main
```

to run the sample.

### Author ###

Name:  Kostas Koyias  
Email: sdi1500071@di.uoa.gr
