#pragma once

#include <stdio.h>

typedef int (*list_compare)(const void* a, const void* b);

struct list_node
{
    struct list_node* next;
    struct list_node* prev;
    void* value;
};

struct list
{
    int count;
    struct list_node* first;
    struct list_node* last;
};

struct list* list_create();
void list_destroy(struct list* list);
void list_clear(struct list* list);
void list_clear_destroy(struct list* list);
void list_push_back(struct list* list, void* value);
void* list_pop_back(struct list* list);
void list_push_front(struct list*, void* value);
void* lsit_pop_front(struct list*);
void* list_remove(struct list* list, struct list_node* node);
void list_print(struct list* list);

void list_bubble_sort(struct list* list, list_compare cmp);
struct list* list_merge_sort(struct list* list, list_compare cmp);
