#include "list.h"
#include "utils.h"

int list_init(list_t *list, const char *name, const size_t node_size, int (*init)(void*, const void*), 
            int (*cmp)(const void*, const void*), int (*print)(const void*), void (*free_data)(void*)){
        if(list == NULL || init == NULL || node_size < 0)
            return -1;

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
        list->free_data = free_data != NULL ? free_data : free;
        
        return 0;
}

int list_is_empty(const list_t *list){
    if(list == NULL)
        return -1;
    return list->head == NULL;
}

/*  check whether an instance of a certain type belongs to a list, comparing it with the list's elements 
    using a type-specific comparison function
    returns a pointer to the item's position if it exists or NULL if it does not */
void *list_search(const list_t* list, const void *data){
    node_t* parser;
    if(list->cmp == NULL || list == NULL || list->head == NULL || data == NULL)
        return NULL;

    for(parser = list->head; parser != NULL; parser = parser->next){
        if(list->cmp(parser->data, data) == 0)
            return parser;
    }
    return NULL;
}

// insert a node to the beginning of a linked list
int list_push(list_t *list, const void *data){
    return list_add(list, data, 1);
}

// insert a node to the end of a linked list
int list_insert(list_t *list, const void *data){
    return list_add(list, data, 0);
}

// insert an item in the list, initialize it's value using function 'init', which was passed as a parameter
int list_add(list_t* list, const void *data, uint8_t at_front){
    node_t *node;
    if(list->init == NULL || list == NULL || data == NULL)
        return -1;

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
    return list->init(node->data, data);
}

// retrieves, but does not remove, the head of a linked list.
void *list_peek(list_t *list){
    if(list == NULL)
        return NULL;
    return list->head;
}

// pop a node from the top of a linked list
node_t *list_pop(list_t *list){
    node_t *node;
    if(list == NULL || list->head == NULL)
        return NULL;

    node = list->head;
    if(node == list->tail)
        list->tail = node->next;
    list->head = node->next;
    list->length--;
    return node;
}

// delete an element of the list, returns 0 in success and -1 if the element given is not a list's member
int list_delete(list_t* list, const void *data){
    node_t *node;

    if(list == NULL || list->head == NULL || data == NULL || list->cmp == NULL)
        return -1;

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
    
    list->free_data(node->data);
    reset(node);
    list->length--;
    return 0;
}

// print all nodes of a list 
int list_print(const list_t *list){
    if(list == NULL || list->head == NULL || list->print == NULL)
        return -1;

    fprintf(stdout, "\n\e[1;4m%s\e[0m\n * length: %d\n * node_size: %d\e[0m\n",
             list->name, list->length, (int)list->node_size);

    return list_for_each(list, list->print);
}

// free all nodes of a list
int list_free(list_t* list){
    node_t *parser, *temp;
    if(list == NULL)
        return -1;

    // de-allocate all memory used
    reset(list->name);
    for(parser = list->head; parser != NULL; parser = temp){
        temp = parser->next;
        list->free_data(parser->data);
        reset(parser);
    }

    // clear all properties
    list->init = NULL;
    list->cmp = NULL;
    list->print = NULL;
    list->free_data = NULL;
    list->head = list->tail = NULL;
    list->length = list->node_size = 0;
    return 0;
}