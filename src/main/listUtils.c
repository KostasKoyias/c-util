#include "list.h"

// apply a non-modifying function to each element
int listForEach(const list_t *list, int (*function)(const void*)){
    node_t *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;  
}

// apply a function to each element of a list that might change its value
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

// return a pointer to the node of the list holding the maximum value
node_t *listBest(list_t *list, uint8_t maxOrMin){
    node_t *best = NULL, *i;
    if(list == NULL || listIsEmpty(list) || list->cmp == NULL)
        return NULL;
    
    for(i = list->head, best = i; i->next != NULL; i = i->next){
        if((maxOrMin == 0 && list->cmp(best, i->next) < 0) || (maxOrMin && list->cmp(best, i->next) > 0))
            best = i->next;
    }
    return best;
}