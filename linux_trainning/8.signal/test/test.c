#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
static void sigHandler(int sig)
{
	static int count = 0;
	if (sig == SIGINT) //ctrl + c;
    {
		count++;
		printf("Caught SIGINT (%d)\n", count);
		return; // Resume execution at point of interruption 
	}
	// Must be SIGQUIT - print a message and terminate the process 
	printf("Caught SIGQUIT - that's enough to terminate it !\n");  //ctrl + \;
	exit(0);
}

int main(int argc, char *argv[])
{
    // Establish same handler for SIGINT and SIGQUIT 
	if (signal(SIGINT,  sigHandler) == SIG_ERR)
    {
		printf("error in signal");
        exit(0);
    }
	if (signal(SIGQUIT, sigHandler) == SIG_ERR)
    {
		printf("error in signal");
        exit(0);
    }
	for (;;) // Loop forever, waiting for signals 
	pause(); // Block until a signal is caught 
}
