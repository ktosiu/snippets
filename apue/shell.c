#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 4096

int main() {
    char command[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(command, MAXLINE, stdin) != NULL) {
        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = 0;

        if ((pid = fork()) < 0) {
            exit(-1);
        }
        else if (pid == 0) {
            execlp(command, command, NULL);
            perror(command);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {
            printf("waitpid error\n");
            exit(-1);
        }

        printf("%% ");
    }
    return 0;
}
