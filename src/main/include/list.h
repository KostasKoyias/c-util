/**********************************************************************************************\
** a generic doubly linked list implementation, appropriate for any data type of your choice, **
** all you need to do is define it's member methods based on your data type's characteristics **
** Author: Kostas Koyias  https://github.com/Kostas_koyias                                     **
\**********************************************************************************************/  
#ifndef list_H_
#define list_H_                           

    #include "define.h"

    typedef struct node{
        void *data;
        struct node *next;
        struct node *prev;
    }node_t;

    typedef struct list{

        // fields
        node_t *head;
        node_t *tail;
        char *name;
        size_t node_size; 
        uint8_t length;   

        // member methods for specific type
        int (*cmp)(const void*, const void*);
        int (*init)(void*, const void*);
        int (*print)(const void*);
        void (*free_data)(void *);
    }list_t;

    // basic list methods
    int list_init(list_t *, const char *, const size_t, int (*)(void *, const void*),
                 int (*)(const void *, const void*), int (*)(const void*), void (*)(void *));
    int list_is_empty(const list_t*);
    void* list_search(const list_t*, const void* data);

    int list_add(list_t*, const void*, uint8_t);
    int list_insert(list_t*, const void*);
    int list_push(list_t*, const void*);

    void *list_peek(list_t *);
    node_t *list_pop(list_t*);
    int list_delete(list_t*, const void*);

    int list_print(const list_t*);
    int list_free(list_t*);

    // utility methods
    int list_map(list_t*, int (*)(void *));
    int list_for_each(const list_t*, int (*)(const void *));
    int list_reduce(list_t *, int, int (*)(void *, const int));
    node_t *list_best(list_t *, uint8_t);

#endif