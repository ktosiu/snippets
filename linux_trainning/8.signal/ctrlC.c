#include <signal.h>
#include <stdio.h>

static void sigHandler(int sig)
{
	printf("Oh there is a ctrl + c !\n");
}

int main(int argc, char *argv[])
{
	int j;
	if (signal(SIGINT, sigHandler) == SIG_ERR) printf("error in signal");

	for (j = 0; ; j++) {
		printf("%d\n", j);
		sleep(3);
	}
}
