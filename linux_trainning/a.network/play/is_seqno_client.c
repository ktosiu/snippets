#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define PORT_NUM "50000"
#define INT_LEN 30
#include <netdb.h>
#define BACKLOG 50

ssize_t readLine(int fd, void *buffer, size_t n) {
    ssize_t numRead;   // # of bytes fetched by last read()
    size_t totRead;    // Total bytes read so far
    char *buf;
    char ch;
    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = (char *)buffer;
    totRead = 0;
    for (;;) {
        numRead = read(fd, &ch, 1);
        if (numRead == -1) {
            if (errno == EINTR) // Interrupted --> restart read()
                continue;
            else
                return -1;      // Some other error
        }
        else if (numRead == 0) {  // EOF
            if (totRead == 0)   // No bytes read; return 0
                return 0;
            else                // Some bytes read; add '\0'
                break;
        }
        else {
            if (totRead < n - 1) {// Discard > (n - 1) bytes
                totRead++;
                *buf++ = ch;
            }

            if (ch == '\n') break;
        }
    }

    *buf = '\0';
    return totRead;
}

int main(int argc, char *argv[]) {
    char     *reqLenStr;         // Requested length of sequence
    char     seqNumStr[INT_LEN]; // Start of granted sequence
    int cfd;
    ssize_t  numRead;
    struct addrinfo  hints;
    struct addrinfo *result, *rp;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s server-host [sequence-len]\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;      // Allows IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    getaddrinfo(argv[1], PORT_NUM, &hints, &result);

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (cfd == -1) continue; // On error, try next address

        if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1) break; // Success
        // Connect failed: close this socket and try next address

        close(cfd);
    }

    freeaddrinfo(result);

    // Send requested sequence length, with terminating newline
    reqLenStr = (argc > 2) ? argv[2] : "1";
    write(cfd, reqLenStr, strlen(reqLenStr));
    write(cfd, "\n", 1) ;

    // Read and display sequence number returned by server
    numRead = readLine(cfd, seqNumStr, INT_LEN);
    printf("Sequence number: %s", seqNumStr);     // Includes '\n'
    exit(EXIT_SUCCESS);                           // Closes 'cfd'
}
