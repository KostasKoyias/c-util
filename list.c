#include "list.h"

/*  check whether an instance of a certain type belongs to a list, comparing it with the list's elements using a type-specific comparison function
    returns a pointer to the item's position if it exists or NULL if it does not*/
void* listSearch(const struct G_list* list, const void *data){
    struct G_node* parser;
    void *result;
    if(list->comp == NULL || list == NULL || list->head == NULL || data == NULL)
        return NULL;
    for(parser = list->head; parser != NULL; parser = parser->next){
        if((result = (list->comp(parser->data, data))) != NULL)
            return result;
    }
    return NULL;
}

/* insert an item in the list, initialize it's value using function 'init', which was passed as a parameter*/
int listInsert(struct G_list* list, const void *data){
    struct G_node* node;
    if(list->assign == NULL || list == NULL || data == NULL)
        return -1;
    if((node = malloc(sizeof(struct G_node))) == NULL){
        perror("listInsert - malloc");
        return -2;
    }
    if((node->data = malloc(list->type_size)) == NULL){
        perror("listInsert - malloc");
        free(node);
        return -3;
    }
    node->next = list->head;
    node->prev = NULL;
    if(list->head != NULL)
        list->head->prev = node;
    list->head = node;
    list->length++;
    if(list->assign == NULL)
        return -4;
    return list->assign(node->data, data);
}

/* delete an element of the list, returns 0 in success and -1 if the element given is not a list's member*/
int listDelete(struct G_list* list, const void *data){
    struct G_node *node;
    if(list == NULL || list->head == NULL || data == NULL || list->comp == NULL)
        return -1;
    if(list->comp(list->head->data, data) == 0){
        node = list->head;
        list->head = node->next;
    }
    else{
        if((node = listSearch(list, data)) == NULL)
            return -1;
        if(node->next != NULL)
            node->next->prev = node->prev;
        if(node->prev != NULL)
            node->prev->next = node->next;
    }
    list->length--;
    if(list->free_data == NULL)
        free(node->data);
    else
        list->free_data(node->data);
    if(node != NULL)
        free(node);
    return 0;
}

/* print all nodes of a list */
int listPrint(const struct G_list *list){
    struct G_node* parser;
    if(list == NULL || list->head == NULL || list->print == NULL)
        return -1;
    fprintf(stdout, "\nlist of length %d and node size %d\n-------------------------------------\n", list->length, (int)list->type_size);
    for(parser = list->head; parser != NULL; parser = parser->next)
        list->print(parser->data);
    return 0;
}

/* free all nodes of a list*/
int listFree(struct G_list* list){
    struct G_node *parser, *temp;
    if(list == NULL)
        return -1;
    for(parser = list->head; parser != NULL; parser = temp){
        temp = parser->next;
        if(list->free_data == NULL)
            free(parser->data);
        else
            list->free_data(parser->data);
        
        free(parser);
    }
    return 0;
}

/* add up all elements in a list and return the sum */
double listSum(const struct G_list* list){
    struct G_node *parser;
    double sum = 0;

    // check whether there is a definition about the value of this kind of data
    if(list->value == NULL)
        return sum;

    // for each element add up it's value in the list
    for(parser = list->head; parser != NULL; parser = parser->next)
        sum += list->value(parser->data);
    return sum;
}

// apply a function to each element of a list
int listMap(struct G_list* list, int (*function)(void*)){
    struct G_node *parser;
    for(parser = list->head; parser != NULL; parser = parser->next)
        function(parser->data);
    return 0;
}

