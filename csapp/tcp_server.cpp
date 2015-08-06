#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

typedef struct sockaddr SA;

int open_listenfd(int port) {
    int listenfd;
    int option = 1;
    struct sockaddr_in server_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&option, sizeof(int));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons((unsigned int)port);

    bind(listenfd, (SA*)&server_addr, sizeof(server_addr));

    listen(listenfd, 10);

    return listenfd;
}

int main() {
    int listenfd = open_listenfd(8000);
    cout << "Listen fd: " << listenfd << endl;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    while(true) {
        int connection_fd = accept(listenfd, (SA*)&client_addr, &client_len);
        cout << "Connected" << endl;
        close(connection_fd);
    }
    return 0;
}
