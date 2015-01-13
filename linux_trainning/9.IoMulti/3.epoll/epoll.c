#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MAX_BUF      1000
#define MAX_EVENTS   5

int main(int argc, char *argv[])
{
	int epfd, ready, fd, s, j, numOpenFds;
	struct epoll_event ev;
	struct epoll_event evlist[MAX_EVENTS];
	char buf[MAX_BUF];

	if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
		printf("%s file...\n", argv[0]);
		exit(0);
    }

	epfd = epoll_create(argc - 1);

	// Open each file on command line, and add it to the "interest list" for the epoll instance 
	for (j = 1; j < argc; j++) 
    {
		fd = open(argv[j], O_RDONLY);
		printf("Opened \"%s\" on fd %d\n", argv[j], fd);
		ev.events = EPOLLIN;  //Only interested in input events
		ev.data.fd = fd;
		epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev); 
	}
	numOpenFds = argc - 1;

	while (numOpenFds > 0) 
    {
		// Fetch up to MAX_EVENTS items from the ready list 
		printf("About to epoll_wait()\n");

		ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);

		if (ready == -1) 
        {
			if (errno == EINTR)continue;  //4, strerror(errno)="Interrupted system call". Restart if interrupted by signal
			else 
			{
				printf("error in epoll_wait");
				exit(0);
			}
		}

		printf("Ready: %d\n", ready);

		// Deal with returned list of events 
		for (j = 0; j < ready; j++) 
        {
			printf(" fd=%d; events: %s%s%s\n", evlist[j].data.fd,
				(evlist[j].events & EPOLLIN)  ? "EPOLLIN "  : "",
				(evlist[j].events & EPOLLHUP) ? "EPOLLHUP " : "",
				(evlist[j].events & EPOLLERR) ? "EPOLLERR " : "" );

			if (evlist[j].events & EPOLLIN) 
            {
				s = read(evlist[j].data.fd, buf, MAX_BUF);
				printf("read %d bytes: %.*s\n", s, s, buf);
			} 
			else if (evlist[j].events & (EPOLLHUP | EPOLLERR)) //Hang up or Error
            {
				printf("closing fd %d\n", evlist[j].data.fd);
				close(evlist[j].data.fd); 
				numOpenFds--;
			}
		}
	}

	printf("All file descriptors closed; bye\n");
	exit(EXIT_SUCCESS);
}

