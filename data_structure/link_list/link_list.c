#include <stdlib.h>
#include <assert.h>
#include "link_list.h"

struct list* list_create()
{
    struct list* pList = (struct list*)malloc(sizeof(struct list));
    pList->count = 0;
    pList->first = 0;
    pList->last = 0;
    return pList;
}

/*Destroy the list structure*/
void list_destroy(struct list* list)
{
    assert(list != 0);
    struct list_node* pNode = list->first;
    while(pNode != list->last)
    {
        struct list_node* current_node = pNode;
        pNode = pNode->next;
        free(current_node);
    }

    free(list->last);
    free(list);
}

/*Clear the values*/
void list_clear(struct list* list)
{
    assert(list != 0);
    struct list_node* pNode = list->first;
    while(pNode != list->last)
    {
        free(pNode->value);
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
    if(list->last == 0)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->count++;
}

void* list_pop_back(struct list* list)
{
    assert(list != 0);
    if(list->count == 0)
    {
        return 0;
    }
    else
    {
        return list_remove(list, list->last);
    }
}

void list_push_front(struct list* list, void* value)
{
    assert(list != 0);
    struct list_node* node = calloc(1, sizeof(struct list_node));
    node->value = value;

    if(list->first == 0)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->count++;
}

void* list_pop_front(struct list* list)
{
    assert(list != 0);

    if(list->count == 0)
    {
        return 0;
    }
    else
    {
        return list_remove(list, list->first);
    }
}

void* list_remove(struct list* list, struct list_node* node)
{
    void* result = 0;
    assert(list != 0);
    assert(node != 0);

    /*List only has one node!*/
    if(node == list->first && node == list->last)
    {
        list->first = 0;
        list->last = 0;
    }
    /*Remove the first node*/
    else if (node == list->first)
    {
        list->first = node->next;
        list->first->prev = 0;
    }
    /*Remove the last node*/
    else if(node == list->last)
    {
        list->last = node->prev;
        list->last->next = 0;
    }
    /*Remove the middle node*/
    else
    {
        struct list_node* prev_node = node->prev;
        struct list_node* next_node = node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }

    list->count--;
    result = node->value;
    free(node);
    return result;
}
