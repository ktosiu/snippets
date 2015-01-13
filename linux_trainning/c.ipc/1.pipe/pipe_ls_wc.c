#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int pfd[2]; // Pipe file descriptors 
	pipe(pfd);  // Create pipe 
	switch (fork()) 
    {
		case -1:
			exit(0);
		case 0: // First child: exec 'ls' to write to pipe 
			close(pfd[0]); // Read end is unused 
			if (pfd[1] != STDOUT_FILENO)  // Defensive check
            { 
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]); 
			}
			execlp("ls", "ls", (char *) NULL); // Writes to pipe 
			exit(0);
		default: // Parent falls through to create next child 
			break;
	}

	switch (fork()) {
		case -1:
			exit(0);	
		case 0: // Second child: exec 'wc' to read from pipe 
			close(pfd[1]);  // Write end is unused 
			if (pfd[0] != STDIN_FILENO) // Defensive check
            { 
				dup2(pfd[0], STDIN_FILENO); 
				close(pfd[0]);
			}
			execlp("wc", "wc", "-l", (char *) NULL); // Reads from pipe 
			exit(0);
		default: // Parent falls through 
			break;
	}
	close(pfd[0]);
	close(pfd[1]);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}

