#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "utils.h"

// constructor wrapper that matches the general-purpose prototype for constructors of this library
int list_init_wrap(void *list, va_list props){
    char *name = va_arg(props, char *);
    size_t node_size = va_arg(props, size_t);
    int (*init)(void*, va_list) = va_arg(props, int (*)(void *, va_list));
    int (*seek)(const void*, const void*) = va_arg(props, int (*)(const void *, const void *));
    int (*cmp)(const void*, const void*) = va_arg(props, int (*)(const void *, const void *));
    void (*print)(void*) = va_arg(props, void (*)(void *));
    void (*destroy)(void*) = va_arg(props, void (*)(void*));
    return list_init(list, name , node_size, init, seek, cmp, print, destroy);
}

// apply a function to each element of the list
int list_foreach(const void *lst, void (*function)(void*)){
    list_foreach_from(lst, function, 1); // start from head
    return 0;  
}

// apply a function to each element of the list in the order requested
int list_foreach_from(const void *lst, void (*function)(void*), int start){
    const list_t *list = lst;
    node_t *parser;
    assert(lst && function);

    for(parser = start ? list->head : list->tail; parser != NULL; parser = start ? parser->next : parser->prev)
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
    assert(list  && list->seek);

    if(list_is_empty(list))
        return NULL;
    
    for(i = list->head, best = i; i->next != NULL; i = i->next)
        if((max_or_min == 0 && list->seek(best, i->next) < 0) || (max_or_min && list->seek(best, i->next) > 0))
            best = i->next;

    return best;
}

void list_reverse(void *list){
    list_t *l = list;
    assert(list);

    for(node_t *parser = l->tail; parser != NULL; parser = parser->next)
        memswap(&(parser->next), &(parser->prev), sizeof(node_t *));
    memswap(&(l->head), &(l->tail), sizeof(node_t *));
}

void list_swap(void *list, void *node0, void *node1){
    list_t *l = list;
    node_t *n0 = node0, *n1 = node1;
    assert(list && node0 && node1 && node0 != node1);

    // n0 should come before n1
    for(node_t *i = l->head; i != NULL; i = i->next){
        if(i == n0)
            break;
        else if(i == n1){
            n1 = n0;
            n0 = i;
            break;
        }
    }

    // update head and tail in case head or tail node gets swapped, then finally swap
    node_update(&(l->head), n0, n1);
    node_update(&(l->tail), n0, n1);
    node_swap(n0, n1);
}

void list_sort(void *list){
    list_t *l = list;
    node_t *min;
    assert(list && l->cmp);

    for(node_t *i = l->head; i != NULL; i = min->next){
        min = i;
        for(node_t *j = i->next; j != NULL; j = j->next){
            if(l->cmp(min->data, j->data) > 0)
                min = j;
        }
        if(i != min)
            list_swap(list, i, min);
    }
}

void list_sort_distinct(void *list){
    list_t *l = list;
    node_t *i, *j, *next;
    assert(list && l->cmp);

    list_sort(list);
    for(i = l->head; i != NULL; i = j)
        for(j = i->next; j != NULL && l->cmp(i->data, j->data) == 0; j = next){
            next = j->next;
            node_erase(l, j);
            node_free(j, l->destroy);
        }
}