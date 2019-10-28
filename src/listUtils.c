#include "include/list.h"

int listForEach(const list_t *list, int (*function)(const void*)){
    node_t *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;  
}

// apply a function to each element of a list
int listMap(list_t* list, int (*function)(void*)){
    node_t *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;
}

int listReduce(list_t *list, int init, int (*reducer)(void *, const int)){
    node_t *i;
    if(list == NULL || reducer == NULL)
        return -1;
    
    for(i = list->head; i != NULL; i = i->next)
        init = reducer(i->data, (const int)init);
    return init;
}

node_t *listMax(list_t *list){
    node_t *max = NULL, *i;
    if(list == NULL || list->comp == NULL)
        return NULL;
    
    for(i = list->head, max = i; i->next != NULL; i = i->next){
        if(list->comp(max, i->next) < 0)
            max = i->next;
    }
    return max;
}