#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define SERVER_FIFO "/tmp/seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct request { // Request (client --> server) 
	pid_t pid;   // PID of client 
	int seqLen;  // Length of desired sequence 
};

struct response { // Response (server --> client) 
	int seqNum;   // Start of sequence 
};

static char clientFifo[CLIENT_FIFO_NAME_LEN];

//Invoked on exit to delete client FIFO
static void removeFifo(void)
{
	unlink(clientFifo);
}

int main(int argc, char *argv[])
{
	int serverFd, clientFd;
	struct request req;
	struct response resp;

	if (argc > 1 && strcmp(argv[1], "--help") == 0)
	{
		printf("%s [seq-len...]\n", argv[0]);
		exit(0);
	}

    // set the process' file mode creation mask to 0
	umask(0); 
	snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long) getpid());

	if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1&& errno != EEXIST) exit(0);

	if (atexit(removeFifo) != 0)exit(0);

	// Construct request message, open server FIFO, and send request 
	req.pid = getpid();
	req.seqLen = (argc > 1) ? atoi(argv[1]) : 1;
	serverFd = open(SERVER_FIFO, O_WRONLY);
	write(serverFd, &req, sizeof(struct request));

	// Open our FIFO, read and display response 
	clientFd = open(clientFifo, O_RDONLY);
	read(clientFd, &resp, sizeof(struct response));
	printf("%d\n", resp.seqNum);
	exit(EXIT_SUCCESS);
}

