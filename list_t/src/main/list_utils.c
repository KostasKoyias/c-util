#include <stdio.h>
#include <string.h>
#include "list.h"

// apply a non-modifying function to each element
int list_for_each(const void *lst, int (*function)(const void*)){
    const list_t *list = lst;
    node_t *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;  
}

// apply a function to each element of a list that might change its value
int list_map(void *lst, int (*function)(void*)){
    list_t *list = lst;
    node_t *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;
}

int list_reduce(void *lst, int init, int (*reducer)(void *, const int)){
    list_t *list = lst;
    node_t *i;
    if(list == NULL || reducer == NULL)
        return -1;
    
    for(i = list->head; i != NULL; i = i->next)
        init = reducer(i->data, (const int)init);
    return init;
}

// return a pointer to the node of the list holding the maximum value
node_t *list_best(void *lst, uint8_t max_or_min){
    list_t *list = lst;
    node_t *best = NULL, *i;
    if(list == NULL || list_is_empty(list) || list->cmp == NULL)
        return NULL;
    
    for(i = list->head, best = i; i->next != NULL; i = i->next){
        if((max_or_min == 0 && list->cmp(best, i->next) < 0) || (max_or_min && list->cmp(best, i->next) > 0))
            best = i->next;
    }
    return best;
}