#include "common.h"

template<typename ElemType>
struct LNode {
    ElemType data;
    LNode<ElemType>* next;
};

// Algorithm 2.8
template<typename ElemType>
Status GetElem_L(LNode<ElemType>* L, int i, ElemType& e) {
    // L is a linklist with head node
    auto p = L->next;
    int j = 1;
    while(p && j < i) {
        p = p->next;
        ++j;
    }
    if(!p || j > i) return ERROR;
    e = p->data;
    return OK;
}

// Algorithm 2.9
template<typename ElemType>
Status ListInsert_L(LNode<ElemType>* L, int i, ElemType e) {
    auto p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p->next;
        ++j;
    }
    LNode<ElemType>* node = new LNode<ElemType>();
    node->data = e;
    node->next = p->next;
    p->next = node;
    return OK;
}

// Algorithm 2.10
template<typename ElemType>
Status ListDelete_L(LNode<ElemType>* L, int i, ElemType& e){
    auto p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p->next;
        ++j;
    }
    auto q = p->next;
    e = q->data;
    p->next = q->next;
    delete q;
    return OK;
}

// Traverse
template<typename ElemType, typename Visit>
void List_Traverse(LNode<ElemType>* L, Visit visit) {
    auto p = L->next;
    while(p){
        visit(p->data);
        p = p->next;
    }
}
