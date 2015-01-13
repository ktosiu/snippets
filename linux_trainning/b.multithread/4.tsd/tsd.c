#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_key_t key;

void *thread2(void *arg)
{
    int tsd = 5;
    printf("thread %ld is running\n",pthread_self());

    //associate a thread-specific value with a key
    //Different threads may bind different values to the same key
    pthread_setspecific(key,(void *)(&tsd));

    printf("thread %ld returns %d\n", pthread_self(), *((int*)pthread_getspecific(key)) );
}

void *thread1(void *arg)
{
    int tsd = 0;
    pthread_t thid2;

    printf("thread %ld is running\n",pthread_self());

    pthread_setspecific(key,(void *)(&tsd));

    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(2);
    printf("thread %ld returns %d\n", pthread_self(), *((int*)pthread_getspecific(key)) );
}

int main(void)
{
    pthread_t thid1;
    printf("main thread begins running\n");

    //create a thread-specific data key visible to all threads in the process
    pthread_key_create(&key,NULL);

    pthread_create(&thid1,NULL,thread1,NULL);
    sleep(5);

    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}
