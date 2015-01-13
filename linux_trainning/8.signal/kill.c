#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int s, sig;
	if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
		printf("%s pid sig-num\n", argv[0]);
 		exit(0);
	}
	sig = atoi(argv[2]);
	s = kill(atoi(argv[1]), sig);
	if (sig != 0) 
    {
		if (s == -1) 
        {
			printf("error in kill");
            exit(0);
		}
	} 
    else 
    { /* Null signal: process existence check */
		if (s == 0) {
			printf("Process exists and we can send it a signal\n");
		} 
		else {
			if (errno == EPERM)
				printf("Process exists, but we don't have permission to send it a signal\n");
			else if (errno == ESRCH) printf("Process does not exist\n");
			else
            {
				printf("error in kill");
				exit(0);
			}
		}
	}
	exit(0);
}

