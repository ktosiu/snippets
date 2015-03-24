#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_FIFO "/tmp/seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct request {  // Request (client --> server)
    pid_t pid;    // PID of client
    int seqLen;   // Length of desired sequence
};

struct response { // Response (server --> client)
    int seqNum;   // Start of sequence
};

int main(int argc, char *argv[]) {
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;

    umask(0);
    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1  && errno != EEXIST) exit(0);
    serverFd = open(SERVER_FIFO, O_RDONLY);

    // Open an extra write descriptor, so that we never see EOF
    dummyFd = open(SERVER_FIFO, O_WRONLY);

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)exit(0);

    for (;;) {  //  Read requests and send responses
        if (read(serverFd, &req, sizeof(struct request))!= sizeof(struct request)) {
            fprintf(stderr, "Error reading request; discarding\n");
            continue; // Either partial read or error
        }

        // Open client FIFO (previously created by client)
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) req.pid);
        clientFd = open(clientFifo, O_WRONLY);

        // Send response and close FIFO
        resp.seqNum = seqNum;
        if (write(clientFd, &resp, sizeof(struct response))!= sizeof(struct response))
            fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);

        close(clientFd);
        seqNum += req.seqLen; // Update our sequence number
    }
}
