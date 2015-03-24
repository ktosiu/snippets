#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int glob = 0;
static sem_t sem;
static void *threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j;
    for (j = 0; j < loops; j++) {
        sem_wait(&sem) ;
        loc = glob;
        loc++;
        glob = loc;
        sem_post(&sem);

    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    loops = (argc > 1) ? atoi(argv[1]) : 10000000;
    sem_init(&sem, 0, 1);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    s = pthread_create(&t2, NULL, threadFunc, &loops);

    s = pthread_join(t1, NULL);
    s = pthread_join(t2, NULL);

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}
