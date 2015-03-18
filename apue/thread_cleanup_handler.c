#include <pthread.h>
#include <stdio.h>
#include <string.h>

void clean_up(void* arg) {
    printf("clean up: %s\n", (char*)arg);
}

void* thread_main1(void* arg) {
    printf("thread1 returning\n");
    pthread_cleanup_push(clean_up, "thread1 first handler");
    if(arg) {
        return NULL;
    }
    pthread_cleanup_pop(0);
    return NULL;
}

void* thread_main2(void* arg) {
    printf("thread2 exiting\n");
    pthread_cleanup_push(clean_up, "thread2 first handler");
    pthread_cleanup_push(clean_up, "thread2 second handler");
    if(arg)
        return NULL;
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_main1, (void*)1);
    pthread_create(&tid2, NULL, thread_main2, (void*)1);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
