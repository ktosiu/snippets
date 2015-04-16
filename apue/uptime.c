#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("usage: %s hostname\n", argv[0]);
        return 0;
    }

    struct addrinfo* ai_list = NULL;
    int ret = getaddrinfo(argv[1], "ruptime", NULL, &ai_list);
    if(ret != 0) {
        perror("getaddrinfo: ");
        return 0;
    }

    for(struct addrinfo* aip = ai_list; aip != NULL; aip = aip->ai_next) {
        int fd = socket(aip->ai_family, SOCK_STREAM, 0);
        if(connect (fd, aip->ai_addr, aip->ai_addrlen) < 0) {
            printf("fail to connect to host\n");
            continue;
        }

        int n = 0;
        char buf[BUFSIZ];
        while((n = recv (fd, buf, BUFSIZ, 0)) > 0) {
            write(STDOUT_FILENO, buf, n);
        }
    }
    return 0;
}
