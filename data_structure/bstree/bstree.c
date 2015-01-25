#include "bstree.h"
#include <stdlib.h>
#include <string.h>

static int default_compare(void* a, void* b)
{
    return strcmp((char*)a, (char*)b);
}

BSTree* BSTree_create(BSTree_compare compare)
{
    BSTree* map = calloc(1, sizeof(BSTree));
    map->compare = compare;
    if(!map->compare) {
        map->compare = default_compare;
    }
    return map;
}

static void BSTree_destroy_callback(BSTreeNode* node)
{
    free(node);
}

void BSTree_destroy(BSTree* map)
{
    if(map)
    {
        BSTree_traverse(map, BSTree_destroy_callback);
        free(map);
    }
}

static BSTreeNode* BSTreeNode_create(BSTreeNode* parent, void* key, void* value)
{
    BSTreeNode* node = calloc(1, sizeof(BSTreeNode));
    node->parent = parent;
    node->key = key;
    node->value = value;
    return node;
}

static void BSTree_setnode(BSTree* map, BSTreeNode* node, void* key, void* value){
    int cmp = map->compare(node->key, key);
    if(cmp <= 0) {
        if(node->left) {
            BSTree_setnode(map, node->left, key, value);
        }
        else {
            node->left = BSTreeNode_create(node, key, value);
        }
    }
    else {
        if(node->right) {
            BSTree_setnode(map, node->right, key, value);
        }
        else {
            node->right = BSTreeNode_create(node, key, value);
        }
    }
}

void BSTree_set(BSTree* map, void* key, void* value) {
    if(map->root == 0) {
        map->root = BSTreeNode_create(0, key, value);
    }
    else {
        BSTree_setnode(map, map->root, key, value);
    }
}

static BSTreeNode* BSTree_getnode(BSTree* map, BSTreeNode* node, void* key) {
    int cmp = map->compare(node->key, key);

    if(cmp == 0) {
        return node;
    }
    else if(cmp < 0) {
        if(node->left)
            return BSTree_getnode(map, node->left, key);
        else
            return 0;
    }
    else {
        if(node->right)
            return BSTree_getnode(map, node->right, key);
        else
            return 0;
    }
}

void* BSTree_get(BSTree* map, void* key) {
    if(map->root == 0) {
        return 0;
    }
    else {
        BSTreeNode* node = BSTree_getnode(map, map->root, key);
        return node ? node->value : 0;
    }
}

static void BSTree_traverse_nodes(BSTreeNode* node, BSTree_traverse_callback cb) {
    if(node) {
        if(node->left) {
            BSTree_traverse_nodes(node->left, cb);
        }
        if(node->right) {
            BSTree_traverse_nodes(node->right, cb);
        }
        cb(node);
    }
}


static void BSTree_inorder_traverse_nodes(BSTreeNode* node, BSTree_traverse_callback cb) {
    if(node) {
        if(node->left) {
            BSTree_traverse_nodes(node->left, cb);
        }

        cb(node);

        if(node->right) {
            BSTree_traverse_nodes(node->right, cb);
        }
    }
}

void BSTree_traverse(BSTree* map, BSTree_traverse_callback cb) {
    if(map->root) {
        BSTree_traverse_nodes(map->root, cb);
    }
}

void BSTree_inorder_traverse(BSTree* map, BSTree_traverse_callback cb) {
    if(map->root) {
        BSTree_inorder_traverse_nodes(map->root, cb);
    }
}
