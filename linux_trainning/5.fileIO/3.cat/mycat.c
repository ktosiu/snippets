#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

char stdbuf[BUFSIZ];

int main(int argc, char** argv)
{
	int fflg = 0;
	register FILE *fi;
	register c;
	int dev, ino = -1;
	struct stat statb;

    //unbuffered, block buffered, and line buffered.
    //default buffer mode: block buffered
	setbuf(stdout, stdbuf);

    //u can change the buffer mode
	for( ; argc>1 && argv[1][0]=='-'; argc--,argv++) 
	{
		switch(argv[1][1]) 
		{
			case 0:
				break;
			case 'u':
                //unbuffered
				setbuf(stdout, (char *)NULL);
				continue;
		}
		break;
	}

    //check if output and input file  are same
	fstat(fileno(stdout), &statb);

    /*
    struct stat {
               dev_t     st_dev;     // ID of device containing file 
               ino_t     st_ino;     // inode number 
               mode_t    st_mode;    // protection 
               nlink_t   st_nlink;   // number of hard links 
               uid_t     st_uid;     // user ID of owner 
               gid_t     st_gid;     // group ID of owner 
               dev_t     st_rdev;    // device ID (if special file) 
               off_t     st_size;    // total size, in bytes 
               blksize_t st_blksize; // blocksize for file system I/O 
               blkcnt_t  st_blocks;  // number of 512B blocks allocated 
               time_t    st_atime;   // time of last access 
               time_t    st_mtime;   // time of last modification 
               time_t    st_ctime;   // time of last status change 
           };
    */

	statb.st_mode &= S_IFMT; //mask for file type, use &= to get the file type
    //regular file, directory, character device, block device, FIFO, symbolic link, socket
    //everything is a file.
	if (statb.st_mode!=S_IFCHR && statb.st_mode!=S_IFBLK) //not a directory not a block device
	{
		dev = statb.st_dev;
		ino = statb.st_ino;
	}

	if (argc < 2) 
	{
		argc = 2;
		fflg++;   //no input file, use stdin as input
	}

    //more than one input file
	while (--argc > 0) 
	{
		if (fflg || (*++argv) [0]=='-' && (*argv) [1]=='\0') 
        {
            fi = stdin;
        }
		else 
		{
			if ((fi = fopen(*argv, "r")) == NULL) 
			{
				fprintf(stderr, "cat: can't open %s\n", *argv);
				continue;
			}
		}

		fstat(fileno(fi), &statb);
		if (statb.st_dev==dev && statb.st_ino==ino) 
		{
			fprintf(stderr, "cat: input %s is output\n", fflg?"-": *argv);
			fclose(fi);
			continue;
		}

        //Copy file contents to stdout
		while ((c = getc(fi)) != EOF) putchar(c);

		if (fi!=stdin) fclose(fi);
	}
	return 0;
}
