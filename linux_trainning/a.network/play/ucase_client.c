#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 10
#define PORT_NUM 50002   // Server port number 

int main(int argc, char *argv[])
{
	struct sockaddr_in6 svaddr;
	int sfd, j;
	size_t msgLen;
	ssize_t numBytes;
	char resp[BUF_SIZE];

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s host-address msg...\n", argv[0]);
		exit(0);
	}
	
	sfd = socket(AF_INET6, SOCK_DGRAM, 0);            // Create client socket 

	memset(&svaddr, 0, sizeof(struct sockaddr_in6));
	svaddr.sin6_family = AF_INET6;
	svaddr.sin6_port = htons(PORT_NUM);
	inet_pton(AF_INET6, argv[1], &svaddr.sin6_addr); 

	// Send messages to server; echo responses on stdout
	for (j = 2; j < argc; j++) 
    {
		msgLen = strlen(argv[j]);
		sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in6));
		
		numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
		printf("Response %d: %.*s\n", j - 1, (int) numBytes, resp);
	}
    exit(EXIT_SUCCESS);
}
