/**********************************************************************************************\
** a generic doubly linked list implementation, appropriate for any data type of your choice, **
** all you need to do is define it's member methods based on your data type's characteristics **
** Author: Kostas Koyias  https://github.com/KostasKoyias                                     **
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
        void (*freeData)(void *);
    }list_t;

    // basic list methods
    int listInit(list_t *, const char *, const size_t, int (*)(void *, const void*),
                 int (*)(const void *, const void*), int (*)(const void*), void (*)(void *));
    int listIsEmpty(const list_t*);
    void* listSearch(const list_t*, const void* data);

    int listAdd(list_t*, const void*, uint8_t);
    int listInsert(list_t*, const void*);
    int listPush(list_t*, const void*);

    void *listPeek(list_t *);
    node_t *listPop(list_t*);
    int listDelete(list_t*, const void*);

    int listPrint(const list_t*);
    int listFree(list_t*);

    // utility methods
    int listMap(list_t*, int (*)(void *));
    int listForEach(const list_t*, int (*)(const void *));
    int listReduce(list_t *, int, int (*)(void *, const int));
    node_t *listBest(list_t *, uint8_t);

#endif