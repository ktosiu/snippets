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
	size_t len; /* Size of shared memory object */
	char *addr;
	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s shm-name string\n", argv[0]);
		exit(0);
	}
	fd = shm_open(argv[1], O_RDWR, 0); /* Open existing object */
	len = strlen(argv[2]);
	ftruncate(fd, len); 
	printf("Resized to %ld bytes\n", (long) len);
	addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	printf("copying %ld bytes\n", (long) len);
	memcpy(addr, argv[2], len); /* Copy string to shared memory */
	exit(EXIT_SUCCESS);
}
