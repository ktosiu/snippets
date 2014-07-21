#include "policy_class.h"
#include "SmartPtr.h"

int main()
{
    IntManager intMgr;
    int* p = intMgr.Create();
    delete p;

    LongManager longManager;
    long* pLong = longManager.Create();
    free(pLong);

    NonCheckingPtr ncip;
    ncip->func();

    CheckingPtr cip(0);
    cip->func();
    return 0;
}
