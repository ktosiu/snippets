#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-n] name\n", progName);
    fprintf(stderr, " -n Use O_NONBLOCK flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int flags, opt;
    mqd_t mqd;
    unsigned int prio;
    void *buffer;
    struct mq_attr attr;
    ssize_t numRead;
    flags = O_RDONLY;
    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
        case 'n': flags |= O_NONBLOCK; break;
        default: usageError(argv[0]);
        }
    }
    if (optind >= argc)
        usageError(argv[0]);
    mqd = mq_open(argv[optind], flags);
    mq_getattr(mqd, &attr);
    buffer = malloc(attr.mq_msgsize);
    numRead = mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
    printf("Read %ld bytes; priority = %u\n", (long) numRead, prio);
    write(STDOUT_FILENO, buffer, numRead);
    write(STDOUT_FILENO, "\n", 1);
    exit(EXIT_SUCCESS);
}
