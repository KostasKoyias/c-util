# README #

Using linked lists of various data types for a long time now, implementing a generic doubly linked list in C was probably a good idea.
It's interface can be found in "list.h".

### How it works ###

To create a doubly linked list of a certain type you need to define it's 'member methods'(see list.h, struct G_list).
After that, you can create a list of this type and apply whatever function(e.g listInsert, listMap etc.) on it.

### How to use it ###

In order to use the generic list(struct G_list) in one of your programs compile with gcc to produce a .o file.
For example:
	gcc -c list.c
will produce a list.o
Then include "list.h" in your main function. Make sure that the "list.h" file either resides into the same folder as your programm 
or you 've specified the path to gcc, using the -L option.
To compile your programm, say 'myprog.c' execute:
	gcc -o myprog myprog.c list.o
and you are set, you can now run the 'myprog' executable.

#### Author ####
Name:  Kostas Koyias
Email: sdi1500071@di.uoa.gr