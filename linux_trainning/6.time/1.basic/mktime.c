#include<time.h>
#include<stdio.h>
int main() {
    time_t timep;
    struct tm *p;
    time(&timep);
    printf("time() : %ld \n", timep);
    p=localtime(&timep);
    timep = mktime(p);
    printf("time()->localtime()->mktime():%ld\n", timep);
    return 0;
}
