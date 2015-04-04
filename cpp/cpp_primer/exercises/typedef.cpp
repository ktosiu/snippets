#include <iostream>

int main() {
    typedef char* pstring;
    const char* p = 0;
    p++; // OK
    // Error: (*p)++;

    const pstring p1 = 0;
    (*p1)++; // OK
    // Error: *p1++;
}
