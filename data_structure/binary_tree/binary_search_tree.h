#include <iostream>
using std::cout;
using std::endl;

template<typename K, typename V>
class BinarySearchTree
{
private:
    struct node
    {
        K key;
        V value;
        node *lchild;
        node *rchild;

        node(K k, V v)
            : key(k), value(v), lchild(0), rchild(0)
        {

        }
    };

    node* root;

    V search_recursive(node* p, K key)
    {
        if(!p) return V();
        if(key < p->key) return search_recursive(p->lchild, key);
        if(key > p->key) return search_recursive(p->rchild, key);
        if(key == p->key) return p->value;
    }

    void insert_recursive(node*& p, K key, V value)
    {
        if(!p) { p = new node(key, value); return; }
        if(key < p->key) insert_recursive(p->lchild, key, value);
        if(key > p->key) insert_recursive(p->rchild, key, value);
        if(key == p->key) return;
    }

    void tranverse_recursive_inorder(node* p)
    {
        if(!p) return;
        if(p->lchild) tranverse_recursive_inorder(p->lchild);
        cout << "key: " << p->key << " value: " << p->value << std::endl;
        if(p->rchild) tranverse_recursive_inorder(p->rchild);
    }

    void destruct_postorder(node *p)
    {
        if(!p) return;
        if(p->lchild) destruct_postorder(p->lchild);
        if(p->rchild) destruct_postorder(p->rchild);
        delete p;
    }

public:
    BinarySearchTree()
        : root(0)
    {
    }

    ~BinarySearchTree()
    {
        destruct_postorder(root);
    }

    V search(K key)
    {
        return search_recursive(root, key);
    }

    void insert(K key, V value)
    {
        insert_recursive(root, key, value);
    }

    void tranverse()
    {
        tranverse_recursive_inorder(root);
    }
};
