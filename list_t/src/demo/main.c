#include <stdio.h>
#include "list.h"
#include "utils.h"
#include "person.h"
#define USERS 4

int main(){
    char* ps[USERS] = {"Thomas", "Kyrie", "Kemba", "Gardner"};
    list_t list;
    int ids[USERS] = {1, 23, 99, 34};

    // initialize list & display initial list
    list_init(&list, "demo-list", sizeof(person_t), init_wrapper, compare, print, destroy);
    for(int i = 0; i < USERS; i++)
        list_insert(&list, ps[i]);
    list_print(&list);

    // reduce list in a couple of ways, extracting statistics
    fprintf(stdout, "\n\e[1;4mStats\e[0m\n* Sum of Ids: %d\n* Prod of ids: %d\n* Max Id: %d, Min Id: %d\n", 
            list_reduce(&list, 0, sum_ids), list_reduce(&list, 1, prod_ids), 
            ((person_t*)(list_best(&list, 0)->data))->id,((person_t*)(list_best(&list, 1)->data))->id);

    // delete record with id equal to 1
    for(int i = 0; i < USERS; i++){
        fprintf(stdout, "\n\e[1;4m>> Removing user with id =\e[0;1;31m %d \e[0;1;4mif one exists\e[0m", ids[i]);
        list_delete(&list, ids + i);
        list_print(&list);
    }

    // free resources
    list_free(&list);
    return 0;
}