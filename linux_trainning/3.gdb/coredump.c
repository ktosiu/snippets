#include <stdio.h>
#include <stdlib.h>
 
int crash()
{
    char *xxx = "crash!!";
    xxx[1] = 'D';
    return 2;
}

int foo()
{
    return crash();
}
 
int main()
{
    return foo();
}
