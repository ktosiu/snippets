#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	sem_t *sem;
	int value;
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s sem-name\n", argv[0]);
		exit(0);
	}
	sem = sem_open(argv[1], 0);

	sem_post(sem);
	sem_getvalue(sem, &value);

	printf("%d\n", value);
	exit(EXIT_SUCCESS);
}
