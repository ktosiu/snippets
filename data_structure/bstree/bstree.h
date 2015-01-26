#pragma once

typedef int (*BSTree_compare)(void* a, void* b);

typedef struct BSTreeNode
{
    void* key;
    void* value;

    struct BSTreeNode* left;
    struct BSTreeNode* right;
    struct BSTreeNode* parent;
} BSTreeNode;

typedef struct BSTree
{
    BSTree_compare compare;
    BSTreeNode* root;
} BSTree;

typedef void (*BSTree_traverse_callback)(BSTreeNode* node);

BSTree* BSTree_create(BSTree_compare compare);
void BSTree_destroy(BSTree *map);

void BSTree_set(BSTree* map, void* key, void* value);
void* BSTree_get(BSTree* map, void* key);

void BSTree_traverse(BSTree* map, BSTree_traverse_callback cb);
void BSTree_inorder_traverse(BSTree* map, BSTree_traverse_callback cb);
void* BSTree_delete(BSTree* map, void* key);
