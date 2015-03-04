#include <stdio.h>

int main() {
    int ch;
    while ((ch = getc(stdin)) != EOF) {
        if (putc(ch, stdout) == EOF) {
            printf("output error\n");
            return -1;
        }
    }

    if (ferror(stdin)) {
        printf("input error\n");
        return -1;
    }

    return 0;
}
