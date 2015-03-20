#include <limits.h>
#include <string.h>
#include <stdio.h>

static char envbuf[ARG_MAX];
extern char** environ;

char* getenv(const char* name) {
    int len = strlen(name);
    for(int i = 0; environ[i] != NULL; i++) {
        if((strncmp(name, environ[i], len) == 0)
           && (environ[i][len] == '=')) {
            strcpy(envbuf, &environ[i][len+1]);
            return envbuf;
        }
    }
    return NULL;
}

int main (int argc, char** argv) {
    printf("%s = %s\n", argv[1], getenv(argv[1]));
    return 0;
}
