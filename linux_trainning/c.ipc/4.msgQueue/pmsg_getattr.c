#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	 main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr;
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s mq-name\n", argv[0]);
		exit(0);
	}
	mqd = mq_open(argv[1], O_RDONLY);
	mq_getattr(mqd, &attr) ;
	printf("Maximum # of messages on queue: %ld\n", attr.mq_maxmsg);
	printf("Maximum message size: %ld\n", attr.mq_msgsize);
	printf("# of messages currently on queue: %ld\n", attr.mq_curmsgs);
	exit(EXIT_SUCCESS);
}
