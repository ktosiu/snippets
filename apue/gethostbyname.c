#include <stdio.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("usage: %s hostname", argv[0]);
        return 0;
    }

    struct hostent* entry = gethostbyname(argv[1]);
    if(entry) {
        printf("offical name: %s\n", entry->h_name);
        printf("alias names:\n");
        for(char* str = *entry->h_aliases; str != NULL; str++) {
            printf("%s ", str);
        }
    }
    return 0;
}
