#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

static char envbuf[ARG_MAX];
extern char** environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char* name, char* buf, int buflen) {
    pthread_once(&init_done, thread_init);
    int len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for(int i = 0; environ[i] != NULL; i++) {
        if((strncmp(name, environ[i], len) == 0)
           && (environ[i][len] == '=')) {
            int oldlen = strlen(&environ[i][len+1]);
            if(oldlen >= buflen) {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf, &environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

int main (int argc, char** argv) {
    char buf[ARG_MAX];
    getenv_r(argv[1], buf, ARG_MAX);
    printf("%s = %s\n", argv[1], buf);
    return 0;
}
