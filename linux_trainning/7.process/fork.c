#include "stdio.h"
#include <unistd.h>

static int idata = 111;

int main()
{
    int   istack = 222;
    pid_t childPid;
    switch (childPid = fork()) {
    case -1:
        printf("error fork");
    case 0:
        /*Child process*/
        idata *= 3;
        istack *= 3;
        break;
    default:
        /*Parent process*/
        sleep(3);
        break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n",
           (long) getpid(),
           (childPid == 0) ? "(child) " : "(parent)",
           idata,
           istack);
    return 0;
}
