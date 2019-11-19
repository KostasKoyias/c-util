#include <stdio.h>
#include "list.h"
#include "person.h"
#define USERS 4

int main(){
    person_t ps[USERS]={{1,"Thomas"}, {2, "Kyrie"}, {15, "Kemba"}, {34, "Gardner"}};
    list_t list;
    int i;

    // initialize list
    list_init(&list, NULL, sizeof(person_t), init, compare, print, free);

    // insert records
    for(i = 0; i < USERS; i++)
        list_insert(&list, ps + i);
    
    // print list
    list_print(&list);
    fprintf(stdout, "\n\e[1;4mStats\e[0m\n* Sum of Ids: %d\n* Prod of ids: %d\n* Max Id: %d, Min Id: %d\n", 
            list_reduce(&list, 0, sum_ids), list_reduce(&list, 1, prod_ids), 
            ((person_t*)(list_best(&list, 0)->data))->id,((person_t*)(list_best(&list, 1)->data))->id);

    // delete all records having odd ids
    fprintf(stdout, "\nRemoving records with odd ids\n");
    for(i = 0; i < USERS; i++){
        if(ps[i].id % 2)
            list_delete(&list, &(ps[i].id));
    }
    
    // print again
    list_print(&list);

    // free resources
    list_free(&list);
    return 0;
}