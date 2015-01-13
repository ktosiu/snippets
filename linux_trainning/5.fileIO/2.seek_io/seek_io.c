#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	size_t len;
	off_t offset;
	int fd, ap, j;
	char *buf;
	ssize_t numRead, numWritten;
	if (argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s file {r<length>|R<length>  |w<string>  |s<offset>}\n",argv[0]);
		exit(0);
	}

    //rw-rw-rw-
	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH); 

	for (ap = 2; ap < argc; ap++) {
		switch (argv[ap][0]) {
		case 'r': // read bytes at current offset, as text 
		case 'R': // read bytes at current offset, in hex 
			len = atoi(&argv[ap][1]);
			buf = malloc(len);
			numRead = read(fd, buf, len);
			if (numRead == 0) {
				printf("%s: end-of-file\n", argv[ap]);
			} 
			else {
				printf("%s: ", argv[ap]);
				for (j = 0; j < numRead; j++) 
				{
					if (argv[ap][0] == 'r') //text
						printf("%c",    isprint((unsigned char) buf[j]) ? buf[j] : '?');
					else//hex
						printf("%02x ", (unsigned int) buf[j]);
				}
				printf("\n");
			}
			free(buf);
			break;
		case 'w': // write string at current offset 
			numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
			printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
			break;
		case 's': // shift file offset 
			offset = atoi(&argv[ap][1]);
			lseek(fd, offset, SEEK_SET);
			printf("%s: seek succeeded\n", argv[ap]);
			break;
		default:
			printf("Argument must start with [rRws]: %s\n", argv[ap]);
		}
	}
	exit(EXIT_SUCCESS);
}
