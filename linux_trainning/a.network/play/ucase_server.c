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
#define PORT_NUM 50002 // Server port number 

int main(int argc, char *argv[])
{
	struct sockaddr_in6 svaddr, claddr;
	int sfd, j;
	ssize_t numBytes;
	socklen_t len;
	char buf[BUF_SIZE];
	char claddrStr[INET6_ADDRSTRLEN];
	sfd = socket(AF_INET6, SOCK_DGRAM, 0);

	memset(&svaddr, 0, sizeof(struct sockaddr_in6));
	svaddr.sin6_family = AF_INET6;
	svaddr.sin6_addr = in6addr_any;     // Wildcard address 
	svaddr.sin6_port = htons(PORT_NUM);
	bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in6));

	// Receive messages, convert to uppercase, and return to client 
	for (;;) 
    {
		len = sizeof(struct sockaddr_in6);
		numBytes = recvfrom(sfd, buf, BUF_SIZE, 0,(struct sockaddr *) &claddr, &len);

		if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr, INET6_ADDRSTRLEN) == NULL)
			printf("Couldn't convert client address to string\n");
		else
			printf("Server received %ld bytes from (%s, %u)\n",(long) numBytes, claddrStr, ntohs(claddr.sin6_port));
			
		for (j = 0; j < numBytes; j++)
			buf[j] = toupper((unsigned char) buf[j]);
			
		sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len);
	}
}
