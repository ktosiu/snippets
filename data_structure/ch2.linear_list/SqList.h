#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

template<typename ElemType>
struct SqList {
    ElemType *elem;
    int length;
    int listSize;
};

// Algorithm 2.3
template<typename ElemType>
Status InitList_Sq(SqList<ElemType>& L) {
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) exit (OVERFLOW);
    L.length = 0;
    L.listSize = LIST_INIT_SIZE;
    return OK;
}

template<typename ElemType>
void DestroyList(SqList<ElemType>& L) {
    if(L.elem)
        free(L.elem);
    L.listSize = 0;
    L.length = 0;
}

template<typename ElemType>
bool ListEmpty(SqList<ElemType>& L){
    return L.length == 0;
}

// Algorithm 2.4
template<typename ElemType>
Status ListInsert_Sq(SqList<ElemType>& L, int i, ElemType e) {
    if(i < 1 || i > L.length + 1 ) return ERROR;
    if(L.length >= L.listSize) {
        ElemType* newBase =
            (ElemType*)realloc(L.elem,
                               (L.listSize + LIST_INCREMENT * sizeof(ElemType)));
        if(!newBase) exit(OVERFLOW);
        L.elem = newBase;
        L.listSize += LIST_INCREMENT;
    }

    ElemType* q = &(L.elem[i-1]);
    for(ElemType* p = &(L.elem[L.length - 1]); p >= q; --p) {
        *(p+1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}

// Algorithm 2.5
template<typename ElemType>
Status ListDelete_Sq(SqList<ElemType>& L, int i, ElemType& e) {
    if(i < 1 || i > L.length) return ERROR;
    ElemType* p = &(L.elem[i-1]);
    e = *p;
    ElemType* q = L.elem + L.length - 1;
    for(++p; p <= q; ++p) *(p-1) = *p;
    --L.length;
    return OK;
}

// Algorithm 2.6
template<typename ElemType, typename Compare>
int LocateElem_Sq(SqList<ElemType>& L, ElemType e, Compare compare) {
    int i = 1; // i is the order
    ElemType* p = L.elem;
    while(i <= L.length && !compare(*p, e)){
        ++i;
        ++p;
    }

    if(i <= L.length) return i;
    else return 0; // Not found
}

// Algorithm 2.7
template<typename ElemType>
void MergeList_Sq(SqList<ElemType> La,
                  SqList<ElemType> Lb,
                  SqList<ElemType> &Lc) {
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;
    Lc.listSize = Lc.length = La.length + Lb.length;
    ElemType* pc = Lc.elem =
        (ElemType*)malloc(Lc.listSize * sizeof(ElemType));
    if(!Lc.elem) exit(OVERFLOW);
    ElemType* pa_end = La.elem + La.length - 1;
    ElemType* pb_end = Lb.elem + Lb.length - 1;
    while(pa <= pa_end && pb <= pb_end) {
        if(*pa < *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }

    while(pa <= pa_end) *pc++ = *pa++;
    while(pb <= pb_end) *pc++ = *pb++;
}

template<typename ElemType, typename Visit>
void ListTraverse(SqList<ElemType> L, Visit visit) {
    for(int i = 0; i < L.length; ++i) {
        visit(L.elem[i]);
    }
}
