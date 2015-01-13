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
	fprintf(stderr, "Usage: %s [-cx] name size [octal-perms]\n", progName);
	fprintf(stderr, " -c Create shared memory (O_CREAT)\n");
	fprintf(stderr, " -x Create exclusively (O_EXCL)\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int flags, opt, fd;
	mode_t perms;
	size_t size;
	void *addr;
	flags = O_RDWR;
	while ((opt = getopt(argc, argv, "cx")) != -1) {
		switch (opt) {
			case 'c': flags |= O_CREAT; break;
			case 'x': flags |= O_EXCL; break;
			default: usageError(argv[0]);
		}
	}
	if (optind + 1 >= argc) usageError(argv[0]);
	size = atoi(argv[optind + 1]);
	perms = (argc <= optind + 2) ? (S_IRUSR | S_IWUSR) : atoi(argv[optind + 2]);
	/* Create shared memory object and set its size */
	fd = shm_open(argv[optind], flags, perms);
	ftruncate(fd, size);
	/* Map shared memory object */
	addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	exit(EXIT_SUCCESS);
}
