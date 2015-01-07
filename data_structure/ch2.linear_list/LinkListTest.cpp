#include "LinkList.h"
#include <iostream>

using namespace std;

int main(){
    LNode<int>* linkList = new LNode<int>();
    linkList->next = 0;

    ListInsert_L(linkList, 1, 1);
    ListInsert_L(linkList, 2, 2);
    ListInsert_L(linkList, 3, 3);
    ListInsert_L(linkList, 4, 4);
    ListInsert_L(linkList, 5, 5);
    List_Traverse(linkList, [](int i){ cout<< i; });
    cout << endl;

    int e = 0;
    ListDelete_L(linkList, 2, e);
    List_Traverse(linkList, [](int i){ cout<< i; });
    cout << endl;

    return 0;
}
