#include <pthread.h>
#include <stdio.h>
#include <string.h>

void* thread_main1(void* arg) {
    printf("thread1 returning\n");
    return (void*)10;
}

void* thread_main2(void* arg) {
    printf("thread2 exiting\n");
    pthread_exit((void*)20);
}

int main() {
    pthread_t tid1, tid2;
    void* ret;

    pthread_create(&tid1, NULL, thread_main1, NULL);
    pthread_create(&tid2, NULL, thread_main2, NULL);
    pthread_join(tid1, &ret);
    printf("thread1 exid code is %d\n", (int)ret);
    pthread_join(tid2, &ret);
    printf("thread2 exid code is %d\n", (int)ret);
    return 0;
}
