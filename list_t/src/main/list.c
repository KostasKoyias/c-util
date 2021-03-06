#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "utils.h"

int list_init(void *lst, const char *name, const size_t node_size, 
            int (*init)(void*, va_list), int (*seek)(const void*, const void*), 
            int (*cmp)(const void*, const void*), void (*print)(void*), void (*destroy)(void*)){
        list_t *list = lst;
        assert(list && init);

        // set common initial list attributes 
        list->head = list->tail = NULL;
        list->node_size = node_size;
        list->length = 0;

        // set list name, if given
        list->name = NULL;
        str_rename(&(list->name), name != NULL ? name : DEFAULT_NAME);

        // member methods of list nodes
        list->init = init;       
        list->seek = seek;
        list->cmp = cmp;
        list->print = print;
        list->destroy = destroy != NULL ? destroy : free;
        return 0;
}

int list_is_empty(const void *lst){
    const list_t *list = lst;
    assert(list);
    return list->head == NULL;
}

/*  check whether an instance of a certain type belongs to a list, comparing it with the list's elements 
    using a type-specific comparison function
    returns a pointer to the item's position if it exists or NULL if it does not */
void *list_search(const void * lst, const void *data){
    const list_t *list = lst;
    node_t* parser;
    assert(list && list->seek && data);

    for(parser = list->head; parser != NULL; parser = parser->next){
        if(list->seek(parser->data, data) == 0)
            return parser;
    }
    return NULL;
}

// insert a node to the beginning of a linked list
int list_push(void *lst, ...){
    list_t *list = lst;
    va_list props;
    va_start(props, lst);
    list_add(list, props, 1);
    va_end(props);
    return 0;
}

// insert a node to the end of a linked list
int list_insert(void *lst, ...){
    list_t *list = lst;
    va_list props;
    va_start(props, lst);
    list_add(list, props, 0);
    va_end(props);
    return 0;
}

// insert an item in the list, initialize it's value using function 'init', which was passed as a parameter
int list_add(void* lst, va_list props, uint8_t at_front){
    list_t *list = lst;
    node_t *node;
    assert(list && list->init);

    // allocate space for a new node
    if((node = malloc(sizeof(node_t))) == NULL)
        return perror_return("list_insert - malloc node", -2);

    if((node->data = malloc(list->node_size)) == NULL){
        reset(node);
        perror_return("list_insert - malloc node->data", -3);
    }

    // add a node either at the front or at the end of a list, operating both as a queue & as a stack
    if(at_front){
        node->prev = NULL;
        node->next = list->head;
        if(list->head != NULL)
            list->head->prev = node;
        else
            list->tail = node;
        list->head = node;
    }
    else{
        node->prev = list->tail;
        node->next = NULL;
        if(list->tail != NULL)
            list->tail->next = node;
        else
            list->head = node;
        list->tail = node;
    }

    list->length++;
    if(list->init == NULL)
        return -4;
    return list->init(node->data, props);
}

// retrieves, but does not remove, the head of a linked list.
void *list_peek(void *lst){
    list_t *list = lst;
    assert(list);
    return list->head;
}

// pop a node from the top of a linked list
node_t *list_pop(void *lst){
    list_t *list = lst;
    node_t *node;
    assert(list && list->head);

    node = list->head;
    if(node == list->tail)
        list->tail = node->next;
    list->head = node->next;
    list->length--;
    return node;
}

// delete an element of the list, returns 0 in success and -1 if the element given is not a list's member
int list_delete(void* lst, const void *data){
    list_t *list = lst;
    node_t *node;
    assert(list && list->head && data && list->seek);

    // find the node to be removed
    if((node = list_search((const list_t*)list, data)) == NULL)
        return -1;

    node_erase(list, node);
    node_free(node, list->destroy);
    list->length--;
    return 0;
}

void list_meta(void *list){
    list_t *l = list;
    assert(list);

    fprintf(stdout, "\n\e[1;4m%s\e[0m\n * length: %d\n * node_size: %d\e[0m\n",
             l->name, l->length, (int)l->node_size);
}

// print all nodes of a list 
void list_print(void *lst){
    list_t *list = lst;
    assert(list && list->print);

    list_meta(lst);
    list_foreach(list, list->print);
}

// free all nodes of a list
void list_free(void* lst){
    list_t *list = lst;
    node_t *parser, *temp;
    assert(list);

    // de-allocate all memory used
    reset(list->name);
    for(parser = list->head; parser != NULL; parser = temp){
        temp = parser->next;
        node_free(parser, list->destroy);
    }

    // clear all properties
    list->init = NULL;
    list->seek = NULL;
    list->cmp = NULL;
    list->print = NULL;
    list->destroy = NULL;
    list->head = list->tail = NULL;
    list->length = list->node_size = 0;
}