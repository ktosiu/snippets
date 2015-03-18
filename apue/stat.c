#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        printf("%s: ", argv[i]);
        struct stat s;
        char* p;
        if (lstat (argv[i], &s) < 0) {
            printf("lstat error\n");
            continue;
        }

        if (S_ISREG(s.st_mode)) {
            p = "regular";
        }
        else if (S_ISDIR(s.st_mode)) {
            p = "directory";
        }
        else if (S_ISCHR(s.st_mode)) {
            p = "charactor special";
        }
        else if (S_ISBLK(s.st_mode)) {
            p = "block special";
        }
        else if (S_ISFIFO(s.st_mode)) {
            p = "fifo";
        }
        else if (S_ISLNK(s.st_mode)) {
            p = "symbolic link";
        }
        else if (S_ISSOCK(s.st_mode)) {
            p = "socket";
        }
        else {
            p = "unknown mode";
        }

        printf("%s\n", p);
    }
    return 0;
}
