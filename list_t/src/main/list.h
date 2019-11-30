/**********************************************************************************************\
** a generic doubly linked list implementation, appropriate for any data type of your choice, **
** all you need to do is define it's member methods based on your data type's characteristics **
** Author: Kostas Koyias  https://github.com/Kostas_koyias                                     **
\**********************************************************************************************/  
#ifndef list_H_
#define list_H_                           

    #include <stdlib.h>
    #include <stdint.h>
    #include <stdarg.h>
    #define DEFAULT_NAME "No name list"

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
        int (*init)(void*, va_list);
        void (*print)(void*);
        void (*destroy)(void *);
    }list_t;

    // node methods
    void node_erase(list_t *, node_t *);
    int node_free(node_t*, void (*)(void* ));

    // basic list methods
    int list_init(void *, const char *, const size_t, int (*)(void *, va_list),
                 int (*)(const void *, const void*), void (*)(void*), void (*)(void *));
    int list_init_wrap(void *, va_list);
    int list_is_empty(const void *);
    void* list_search(const void *, const void* data);

    int list_add(void *, va_list, uint8_t);
    int list_insert(void *, ...);
    int list_push(void *, ...);

    void *list_peek(void *);
    node_t *list_pop(void *);
    int list_delete(void *, const void*);

    void list_print(void *);
    void list_free(void *);

    // utility methods
    void list_reverse(void *);
    int list_foreach(const void *, void (*)(void *));
    int list_reduce(void *, int, int (*)(void *, const int));
    node_t *list_best(void *, uint8_t);

#endif