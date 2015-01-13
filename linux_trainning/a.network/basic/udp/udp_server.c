#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int server_sockfd;
	int len;
	struct sockaddr_in my_addr;   
    struct sockaddr_in remote_addr; 
	int sin_size;
	char buf[BUFSIZ];  

	memset(&my_addr,0,sizeof(my_addr)); 
	my_addr.sin_family=AF_INET; 
	my_addr.sin_addr.s_addr=INADDR_ANY;
	my_addr.sin_port=htons(8000); 
	
	if((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)
	{  
		perror("socket");
		return 1;
	}
 
	if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("bind");
		return 1;
	}
	sin_size=sizeof(struct sockaddr_in);
	printf("waiting for a packet...\n");
	
	if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,&sin_size))<0)
	{
		perror("recvfrom"); 
		return 1;
	}
	printf("received packet from %s:\n",inet_ntoa(remote_addr.sin_addr));
	buf[len]='\0';
	printf("contents: %s\n",buf);
	close(server_sockfd);
    return 0;
}
