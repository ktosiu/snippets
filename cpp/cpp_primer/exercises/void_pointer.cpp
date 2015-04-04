#include <iostream>

int main () {
    int i = 100;
    void* p = &i; // OK. void* can point to any type
    // Wrong:  p++; p--; *p;
    int* pi = (int*)p;
    std::cout << *pi << std::endl;
}
