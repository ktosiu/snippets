#include "binary_search_tree.h"

int main()
{
    BinarySearchTree<int, int> bst;
    bst.insert(4, 9);
    bst.insert(3, 9);
    bst.insert(9, 9);
    bst.insert(4, 9);

    bst.tranverse();
}
