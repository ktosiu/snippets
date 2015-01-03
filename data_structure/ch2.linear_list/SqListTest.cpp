#include "SqList.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    SqList<int> sqList;
    InitList_Sq(sqList);
    ListInsert_Sq(sqList, 1, 10);

    int i = LocateElem_Sq(sqList, 10, std::equal_to<int>());
    cout << i << endl;

    int e;
    ListDelete_Sq(sqList, 1, e);
    cout << sqList.length << endl;
    cout << e << endl;

    SqList<int> la, lb, lc;
    InitList_Sq(la);
    ListInsert_Sq(la, 1, 1);
    ListInsert_Sq(la, 2, 3);
    ListInsert_Sq(la, 3, 5);
    ListInsert_Sq(la, 4, 7);
    ListTraverse(la, [](int item){ cout << item; });
    cout << endl;

    InitList_Sq(lb);
    ListInsert_Sq(lb, 1, 2);
    ListInsert_Sq(lb, 2, 4);
    ListInsert_Sq(lb, 3, 6);
    ListInsert_Sq(lb, 4, 8);
    ListTraverse(lb, [](int item){ cout << item; });
    cout << endl;

    InitList_Sq(lc);
    MergeList_Sq(la, lb, lc);
    ListTraverse(lc, [](int item){ cout << item; });
    cout << endl;
    return 0;
}
