#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s shm-name\n", argv[0]);
        exit(0);
    }

	shm_unlink(argv[1]);
	exit(EXIT_SUCCESS);
}

