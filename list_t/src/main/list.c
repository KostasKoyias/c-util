#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "utils.h"

int node_free(node_t *node, void (*destroy)(void *)){
    void (*destructor)(void *) = destroy ? destroy : free;
    assert(node);

    destructor(node->data);
    reset(node->data);
    reset(node);
    return 0;
}

void list_init(void *lst, const char *name, const size_t node_size, int (*init)(void*, va_list), 
            int (*cmp)(const void*, const void*), int (*print)(const void*), void (*destroy)(void*)){
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
        list->cmp = cmp;
        list->print = print;
        list->destroy = destroy != NULL ? destroy : free;
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
    assert(list && list->cmp && list->head && data);

    for(parser = list->head; parser != NULL; parser = parser->next){
        if(list->cmp(parser->data, data) == 0)
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
    assert(list && list->head && data && list->cmp);

    // find the node to be removed
    if((node = list_search((const list_t*)list, data)) == NULL)
        return -1;

    // update head & tail
    if(node == list->head)
        list->head = node->next;
    if(node == list->tail)
        list->tail = node->prev;

    // update next & previous nodes
    if(node->prev != NULL)
        node->prev->next = node->next;
    if(node->next != NULL)
        node->next->prev = node->prev;
    
    node_free(node, list->destroy);
    list->length--;
    return 0;
}

// print all nodes of a list 
void list_print(const void *lst){
    const list_t *list = lst;
    assert(list && list->head && list->print);

    fprintf(stdout, "\n\e[1;4m%s\e[0m\n * length: %d\n * node_size: %d\e[0m\n",
             list->name, list->length, (int)list->node_size);

    list_for_each(list, list->print);
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
    list->cmp = NULL;
    list->print = NULL;
    list->destroy = NULL;
    list->head = list->tail = NULL;
    list->length = list->node_size = 0;
}