#include <stdio.h>
#include "bstree.h"

void print_node(BSTreeNode* node) {
    printf("%s ", node->value);
}

int main()
{
    BSTree* map = BSTree_create(0);

    BSTree_set(map, "d", "d_value");
    BSTree_set(map, "a", "a_value");
    BSTree_set(map, "b", "b_value");
    BSTree_set(map, "c", "c_value");

    BSTree_traverse(map, (BSTree_traverse_callback)print_node);
    printf("\n");
    BSTree_inorder_traverse(map, (BSTree_traverse_callback)print_node);
    printf("\n");
    /*BSTree_destroy(map);*/
    return 0;
}
