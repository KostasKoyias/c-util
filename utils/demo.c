#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define PHRASE "Hello world!"

int main(){

    // create a string
    char *str = malloc(strlen(PHRASE) + 1);
    strcpy(str, PHRASE);

    fprintf(stdout, "last_index_of: %d %d %d %d\n", 
    last_index_of('H', str), last_index_of('!', str), last_index_of('o', str), last_index_of('a', str));

    fprintf(stdout, "counts occurrences: %d %d\n", str_count(str, 'o'), str_count(str, 'a'));

    fprintf(stdout, "Renaming string\nv1: %s\n", str);
    str_rename(&str, "A way bigger than the previous string, realloc required");
    fprintf(stdout, "v2: %s\n", str);
    str_rename(&str, "v3: a tiny one");
    fprintf(stdout, "%s\n", str);

    reset(str); // free & set to NULL
    return 0;
}