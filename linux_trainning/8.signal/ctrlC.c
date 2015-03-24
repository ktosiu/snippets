#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void sigHandler(int sig) {
    printf("Oh there is a ctrl + c !\n");
}

int main() {
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        printf("error in signal");

    for (int j = 0; ; j++) {
        printf("%d\n", j);
        sleep(3);
    }
}
