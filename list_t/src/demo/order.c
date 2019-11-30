#include <stdio.h>
#include "list.h"
#include "utils.h"
#include "person.h"
#define USERS 4

int main(){
    char* ps[USERS] = {"Thomas", "Kyrie", "Kemba", "Gardner"};
    list_t list;

    // initialize list & display initial state
    list_init(&list, "order-list", sizeof(person_t), init_wrapper, compare, print, destroy);
    for(int i = 0; i < USERS; i++)
        list_insert(&list, ps[i]);
    list_print(&list);

    // reverse list
    fprintf(stdout, "\e[1;4m\n>> Reversing the list\e[0m");
    list_reverse(&list);
    list_print(&list);

    // swap first and last elements
    fprintf(stdout, "\e[1;4m\n>> Swapping head with tail\e[0m");
    list_swap(&list, list.head, list.tail);
    list_print(&list);

    // sort list using the comparator provided
    fprintf(stdout, "\e[1;4m\n>> Sort list using the comparator provided\e[0m");
    list_sort(&list);
    list_print(&list);

    // free resources
    list_free(&list);
    return 0;
}