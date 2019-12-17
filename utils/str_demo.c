#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define PHRASE "Hello world, this is a demo!"
#define COLOR "\e[1;32m"
#define RESET "\e[0m"

int main(){

    // create a string
    char *str = malloc(strlen(PHRASE) + 1), *cs = "H!oa";
    strcpy(str, PHRASE);

    fprintf(stdout, "\e[1;4m >> last_index_of\e[0m: ");
    while(*cs != '\0'){
        fprintf(stdout, "'%c' : %d, ", *cs, last_index_of(*cs, str));
        cs++;
    }
    fprintf(stdout, "in \"\e[4m%s\e[0m\"\n", str);

    fprintf(stdout, "\n\e[1;4m >> Count occurrences of 'o' and 'e'\e[0m: %d %d\n",
    str_count(str, 'o'), str_count(str, 'e'));

    fprintf(stdout, "\n\e[1;4m >> Renaming string\e[0m\nv1: %s\n", str);
    str_rename(&str, "A string, way bigger than the previous string, reallocating space was required");
    fprintf(stdout, "v2: %s\n", str);
    str_rename(&str, "v3: A tiny one, tinyyy!__tiny");
    fprintf(stdout, "%s\n", str);

    str = surround_with(str, "tiny", COLOR, RESET);
    fprintf(stdout, "\n\e[1;4m >> Surrounding \"tiny\" with color codes in string\e[0m\n --> %s\n", str);

    remove_all(str, "tiny");
    fprintf(stdout, "\n\e[1;4m >> Removing \"tiny\" from the string\e[0m --> %s\n", str);

    reset(str); // free & set to NULL
    return 0;
}