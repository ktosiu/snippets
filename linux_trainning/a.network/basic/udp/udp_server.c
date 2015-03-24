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

    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        perror("socket:");
        return -1;
    }

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))<0) {
        perror("bind:");
        return -1;
    }

    socklen_t sin_size = sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");

    ssize_t len = 0;
    if((len = recvfrom(sockfd, buf, BUFSIZ, 0, (struct sockaddr*)&client_addr, &sin_size)) < 0) {
        perror("recvfrom:");
        return -1;
    }

    printf("received packet from %s:\n", inet_ntoa(client_addr.sin_addr));
    buf[len]='\0';
    printf("contents: %s\n", buf);
    close(sockfd);
    return 0;
}
