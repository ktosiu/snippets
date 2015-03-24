#include <time.h>
#include <stdio.h>
int main()
{
    char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p=localtime(&timep); /*取得当地时间*/
    printf("%d_%d_%d\n", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
    printf("%s_%d:%d:%d\n", wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec);
    return 0;
}
