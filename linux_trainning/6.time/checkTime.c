#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct timeval tvBefore;
    struct timeval tvAfter;

    gettimeofday(&tvBefore, NULL);

    long total = 0;
    int  i=0;
    for  (i=0; i< 10000; i++) total +=i;

    gettimeofday(&tvAfter, NULL);

    printf("%ld u seconds used to calculate %ld \n",
           ((long) tvAfter.tv_sec*10000000 +
            (long) tvAfter.tv_usec) -
           ((long) tvBefore.tv_sec*10000000 +
            (long) tvBefore.tv_usec), total);

    return 0;
}
