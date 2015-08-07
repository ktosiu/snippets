#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h> // memset
#include <unistd.h> 

typedef struct sockaddr SA;

int open_listen_fd(int port) {
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(listen_fd < 0) {
        perror("socket:");
        return -1;
    }

    if (bind(listen_fd, (SA*)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind:");
        return -1;
    }

    //max queue for pending connections 5
    listen(listen_fd, 5);

    return listen_fd;
}

int main(int argc, char** argv) {
    int listen_fd = open_listen_fd(8000);
    if(listen_fd < 0) return -1;
        
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
    if(conn_fd < 0) {
        perror("accept:");
        return -1;
    }

    close(conn_fd);
    close(listen_fd);
    return 0;
}
