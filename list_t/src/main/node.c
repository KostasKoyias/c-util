#include <assert.h>
#include "utils.h"
#include "list.h"

void node_update(void *ptr, void *node0, void *node1){
    node_t **head_ptr = ptr, *n0 = node0, *n1 = node1;

    if((*head_ptr) == n0)
        *head_ptr = n1;
    else if((*head_ptr) == n1)
        *head_ptr = n0;
}

void node_replace(void *a, void *b){
    node_t *n0 = a, *n1 = b;
    assert(a && b);

    if(n0->prev != NULL && n0->prev != n1)
        n0->prev->next = n1;
    else if(n0->prev != NULL && n0->prev->prev != NULL)
        n0->prev->prev->next = n0;

    if(n0->next != NULL && n0->next != n1)
        n0->next->prev = n1;
    else if(n0->next != NULL && n0->next->next != NULL)
        n0->next->next->prev = n0;
}

// swap arcs of adjacent nodes based on prev pointer
int node_prev_swap(void *a, void *b){
    node_t *n0 = a, *n1 = b;
    assert(a && b);

    if(n1->prev == n0){
        n1->prev = n0->prev;
        n0->prev = n1;
        return 1;
    }

    return 0;
}

// swap arcs of adjacent nodes based on next pointer
int node_next_swap(void *a, void *b){
    node_t *n0 = a, *n1 = b;
    assert(a && b);

    if(n0->next == n1){
        n0->next = n1->next;
        n1->next = n0;
        return 1;
    }

    return 0;
}

void node_swap(void *a, void *b){
    node_t *n0 = a, *n1 = b;
    assert(a && b);

    node_replace(n0, n1);
    node_replace(n1, n0);
    if(!node_prev_swap(n0, n1))
        memswap(&(n0->prev), &(n1->prev), sizeof(node_t *));

    if(!node_next_swap(n0, n1))
        memswap(&(n0->next), &(n1->next), sizeof(node_t *));
}

void node_erase(void *l, void *n){
    list_t *list = l;
    node_t *node = n;
    assert(l && n);

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
    node->next = node->prev = NULL;
}

int node_free(void *n, void (*destroy)(void *)){
    node_t *node = n;
    void (*destructor)(void *) = destroy ? destroy : free;

    assert(n);
    destructor(node->data);
    reset(node->data);
    reset(node);
    return 0;
}