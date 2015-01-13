#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags;

	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

    //not help or not enough parameters
	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s old-file new-file\n", argv[0]);
		exit(0);
	}

	inputFd = open(argv[1], O_RDONLY);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	// rw-rw-rw- 
	outputFd = open(argv[2], openFlags, filePerms);

	// Transfer data until we encounter end of input or an error 
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	{
		if (write(outputFd, buf, numRead) != numRead)
		{
			printf("couldn't write whole buffer\n");
			exit(0);
		}
	}

	close(inputFd);
	close(outputFd);

	return 0;
}
