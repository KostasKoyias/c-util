#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// constructor wrapper that matches the general-purpose prototype for constructors of this library
int list_init_wrap(void *list, va_list props){
    char *name = va_arg(props, char *);
    size_t node_size = va_arg(props, size_t);
    int (*init)(void*, va_list) = va_arg(props, int (*)(void *, va_list));
    int (*cmp)(const void*, const void*) = va_arg(props, int (*)(const void *, const void *));
    void (*print)(void*) = va_arg(props, void (*)(void *));
    void (*destroy)(void*) = va_arg(props, void (*)(void*));
    return list_init(list, name , node_size, init, cmp, print, destroy);
}

// apply a function to each element of the list
int list_foreach(const void *lst, void (*function)(void*)){
    const list_t *list = lst;
    node_t *parser;
    assert(lst && function);

    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;  
}

int list_reduce(void *lst, int init, int (*reducer)(void *, const int)){
    list_t *list = lst;
    node_t *i;
    assert(list && reducer);
    
    for(i = list->head; i != NULL; i = i->next)
        init = reducer(i->data, (const int)init);
    return init;
}

// return a pointer to the node of the list holding the maximum value
node_t *list_best(void *lst, uint8_t max_or_min){
    list_t *list = lst;
    node_t *best = NULL, *i;
    assert(list  && list->cmp);

    if(list_is_empty(list))
        return NULL;
    
    for(i = list->head, best = i; i->next != NULL; i = i->next)
        if((max_or_min == 0 && list->cmp(best, i->next) < 0) || (max_or_min && list->cmp(best, i->next) > 0))
            best = i->next;

    return best;
}