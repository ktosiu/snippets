#include <time.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int numPipes, j, ready, randPipe, numWrites;

	int (*pfds)[2]; // File descriptors for all pipes

	struct pollfd *pollFd;
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s num-pipes [num-writes]\n", argv[0]);
		exit(0);
	}

	// Allocate the arrays that we use. The arrays are sized according to the number of pipes specified on command line 
	numPipes = atoi(argv[1]);

	pfds   = calloc(numPipes, sizeof(int [2]));       //one pipe two port(read port and write port)
	pollFd = calloc(numPipes, sizeof(struct pollfd)); //one pipe one poll fd

	// Create the number of pipes specified on command line 
	// pipe will be introduced later
	for (j = 0; j < numPipes; j++)
	{
		pipe(pfds[j]);
	}

	numWrites = (argc > 2) ? atoi(argv[2]) : 1; //n writes operation

	srandom((int) time(NULL)); //set seed to generate random

    char buf[32];
	for (j = 0; j < numWrites; j++) 
    {
		randPipe = random() % numPipes;   //select a random pipe
		printf("Writing to fd: %3d (read fd: %3d)\n",pfds[randPipe][1], pfds[randPipe][0]); //read and write pipes are paired
        sprintf(buf, "%daaaaa", randPipe);
		write(pfds[randPipe][1], buf, sizeof(buf));
        printf("Write in [%s]\n", buf);
	}

	/* Build the file descriptor list to be supplied to poll(). This list
	is set to contain the file descriptors for the read ends of all of the pipes. */
	for (j = 0; j < numPipes; j++) 
    {
		pollFd[j].fd = pfds[j][0];
		pollFd[j].events = POLLIN;
	}
	ready = poll(pollFd, numPipes, -1);
	// Nonblocking 
	printf("poll() returned: %d\n", ready);
	// Check which pipes have data available for reading 
	for (j = 0; j < numPipes; j++)
	{
		if (pollFd[j].revents & POLLIN)
        {
		    printf("Readable: %d %3d\n", j, pollFd[j].fd);
            read( pollFd[j].fd, buf, sizeof(buf) );
            printf("Read out [%s]\n", buf);
        }
	}
	exit(EXIT_SUCCESS);
}
