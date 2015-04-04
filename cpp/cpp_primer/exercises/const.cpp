#include <iostream>

int main () {
    int i = 0;
    int& ri = i;
    ri = 1;
    const int& cri = i;
    // Error: cri = 1;
    // Error: const int& const ccri = i;

    int* pi = &i;
    *pi = 2;
    pi++;

    const int* cpi = &i;
    // Error: *cpi = 3;
    cpi++;

    int *const pci = &i;
    *pci = 3;
    // Error: pci++;

    const int *const ccpi = &i;
    // Error: *ccpi = 4;
    // Error: ccpi++;

    return 0;
}
