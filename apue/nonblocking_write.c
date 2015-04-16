#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

char buf[500000];

int main() {
    int ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);
    set_fl(STDOUT_FILENO, O_NONBLOCK);

    char* ptr = buf;
    while(ntowrite > 0) {
        errno = 0;
        int nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if(nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    return 0;
}
