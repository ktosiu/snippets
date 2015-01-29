#include <stdlib.h>
#include <assert.h>
#include "link_list.h"

struct list* list_create()
{
    struct list* pList = (struct list*)malloc(sizeof(struct list));
    pList->head = 0;
    return pList;
}

/*Destroy the list structure*/
void list_destroy(struct list* list)
{
    assert(list != 0);
    struct list_node* node = list->head;
    while(node != 0)
    {
        struct list_node* current_node = node;
        node = node->next;
        free(current_node);
    }
}

/*Clear the values*/
void list_clear(struct list* list)
{
    assert(list != 0);
    struct list_node* node = list->head;
    while(node != 0)
    {
        free(node->value);
        node = node->value;
    }
}

void list_clear_destroy(struct list* list)
{
    list_clear(list);
    list_destroy(list);
}

void list_push_back(struct list* list, void* value)
{
    struct list_node* node = calloc(1, sizeof(struct list_node));
    assert(node != 0);
    node->value = value;
    if(list->head == 0)
    {
        list->head = node;
    }
    else
    {
        struct list_node* p = list->head;
        while(p->next) p = p->next;
        p->next = node;
    }
}

void* list_pop_back(struct list* list)
{
    assert(list != 0);
    if(list->head)
    {
        struct list_node* node = list->head;
        while(node->next) node = node->next;
        return list_remove(list, node);
    }
    else
    {
        return 0;
    }
}

void list_push_front(struct list* list, void* value)
{
    assert(list != 0);
    struct list_node* node = calloc(1, sizeof(struct list_node));
    node->value = value;

    if(list->head == 0)
    {
        list->head = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
}

void* list_pop_front(struct list* list)
{
    assert(list != 0);
    if(list->head)
    {
        return list_remove(list, list->head);
    }
    else
    {
        return 0;
    }
}

void* list_remove(struct list* list, struct list_node* node)
{
    void* result = 0;
    assert(list != 0);
    assert(node != 0);

    /*List only has one node!*/
    if(node == list->head)
    {
        list->head = node->next;
    }
    /*Remove other nodes*/
    else
    {
        // Get prev
        struct list_node* prev = list->head;
        while(prev->next != node) prev = prev->next;
        prev->next = node->next;
    }

    result = node->value;
    free(node);
    return result;
}

void list_print(struct list* list)
{
    assert(list);
    struct list_node* node = list->head;
    while(node)
    {
        printf("%s\n", node->value);
        node = node->next;
    }
}

void list_node_swap(struct list_node* a, struct list_node* b)
{
    void* temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void list_bubble_sort(struct list* list, list_compare cmp)
{
    assert(list != 0);
    int sorted = 1;

    do {
        sorted = 1;
        for(struct list_node* cur = list->head;
            cur != 0;
            cur = cur->next)
        {
            if(cur->next)
            {
                if(cmp(cur->value, cur->next->value) > 0)
                {
                    list_node_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    }
    while(!sorted);
}

void list_reverse(struct list* list) {
    assert(list != 0);
    struct list_node* prev = 0;
    struct list_node* current = list->head;

    while(current) {
        struct list_node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}
