#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "include/list.h"
#define NAME 20
#define USERS 4

// a list holding data of type 'person_t' will be created'
typedef struct person{
    int id;
    char name[NAME];
}person_t;

// person_t member methods are defined below
int compare(const void *p1, const void *vid){
    assert(p1 != NULL && vid != NULL);
    const person_t *pp1 = p1;
    const int *id = vid;
    return pp1->id - *id;
}

int init(void *p1, const void *p2){
    if(p1 == NULL || p2 == NULL)
        return -1;

    person_t *pp1 = (person_t*)p1, *pp2 = (person_t *)p2;
    pp1->id = pp2->id;
    strcpy(pp1->name, pp2->name);
    return 0;
}

int print(const void *p1){
    if(p1 == NULL)
        return -1;

    const person_t *pp1 = (person_t*)p1;
    fprintf(stdout, "\nId: %d\nName: %s\n", pp1->id, pp1->name);
    return 0;
}

int sumIds(void *data, int total){
    person_t *p = data;
    if(data == NULL)
        return -1;
    return p->id + total;
}

int prodIds(void *data, int total){
    person_t *p = data;
    if(data == NULL)
        return -1;
    return p->id * total;
}

int main(){
    person_t ps[USERS]={{1,"Thomas"}, {2, "Kyrie"}, {15, "Kemba"}, {34, "Gardner"}};
    list_t list;
    int i;

    // initialize list
    listInit(&list, NULL, sizeof(person_t), init, compare, print, free);

    // insert records
    for(i = 0; i < USERS; i++)
        listInsert(&list, ps + i);
    
    // print list
    listPrint(&list);
    fprintf(stdout, "\n\e[1;4mStats\e[0m\n* Sum of Ids: %d\n* Prod of ids: %d\n* Max Id: %d\n", 
            listReduce(&list, 0, sumIds), listReduce(&list, 1, prodIds), ((person_t*)(listMax(&list)->data))->id);

    // delete all records having odd ids
    fprintf(stdout, "\nRemoving records with odd ids\n");
    for(i = 0; i < USERS; i++){
        if(ps[i].id % 2)
            listDelete(&list, &(ps[i].id));
    }
    
    // print again
    listPrint(&list);

    // free resources
    listFree(&list);
    return 0;
}