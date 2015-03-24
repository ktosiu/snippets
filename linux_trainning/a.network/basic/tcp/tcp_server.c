#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char buf[BUFSIZ];

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);

    int socketfd = socket(PF_INET, SOCK_STREAM, 0);

    if(socketfd < 0) {
        perror("socket:");
        return -1;
    }

    if (bind(socketfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind:");
        return -1;
    }

    //max queue for pending connections 5
    listen(socketfd, 5);

    socklen_t sin_size = sizeof(struct sockaddr_in);
    int conn_fd = accept(socketfd, (struct sockaddr*)&client_addr, &sin_size);
    if(conn_fd < 0) {
        perror("accept:");
        return -1;
    }

    printf("accept client %s\n", inet_ntoa(client_addr.sin_addr));

    const char* welcome = "Welcome to my server\n";

    send(conn_fd, welcome, strlen(welcome), 0);

    ssize_t len = 0;
    while((len = recv(conn_fd, buf, BUFSIZ, 0)) > 0) {
        buf[len]='\0';
        printf("%s\n",buf);
        if(send(conn_fd, buf, len, 0) < 0) {
            perror("write:");
            return -1;
        }
    }

    close(conn_fd);
    close(socketfd);
    return 0;
}
