#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char *addr;
    struct stat sb;
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s shm-name\n", argv[0]);
        exit(0);
    }
    fd = shm_open(argv[1], O_RDONLY, 0); /* Open existing object */
    fstat(fd, &sb);
    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    write(STDOUT_FILENO, addr, sb.st_size);
    printf("\n");
    exit(EXIT_SUCCESS);
}
