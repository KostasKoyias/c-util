#include <stdio.h>
#include "list.h"
#include "person.h"
#define USERS 4

int main(){
    char* ps[USERS] = {"Thomas", "Kyrie", "Kemba", "Gardner"};
    list_t list;
    int i;

    // initialize list
    list_init(&list, "demo-list", sizeof(person_t), init_wrapper, compare, print, destroy);

    // insert records
    for(i = 0; i < USERS; i++)
        list_insert(&list, ps[i]);
    
    // print list
    list_print(&list);
    fprintf(stdout, "\n\e[1;4mStats\e[0m\n* Sum of Ids: %d\n* Prod of ids: %d\n* Max Id: %d, Min Id: %d\n", 
            list_reduce(&list, 0, sum_ids), list_reduce(&list, 1, prod_ids), 
            ((person_t*)(list_best(&list, 0)->data))->id,((person_t*)(list_best(&list, 1)->data))->id);

    // delete all records having odd ids
    i = 1;
    fprintf(stdout, "\n\e[1;4m>> Removing user with id = %d\e[0m", i);
    list_delete(&list, &i);
    list_print(&list);

    // reverse list
    fprintf(stdout, "\e[1;4m\n>> Reversing the list\e[0m");
    list_reverse(&list);
    list_print(&list);

    // free resources
    list_free(&list);
    return 0;
}