#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
    int fd;
    if ((fd = creat("file.hole", O_CREAT)) < 0) {
        printf("creat error!\n");
        return -1;
    }

    if (write(fd, buf1, 10) != 10) {
        printf("buf1 write error\n");
        return -1;
    }
    /*offset = 10*/

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        printf("lseek error\n");
        return -1;
    }
    /*offset = 16384*/

    if (write(fd, buf2, 10) != 10) {
        printf("buf2 write error\n");
        return -1;
    }
    /*offset = 16394*/

    return 0;
}
