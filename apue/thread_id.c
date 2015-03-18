#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void print_ids(const char* thread_name) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid %u tid %u\n", thread_name, pid, (unsigned int)tid);
}

void* thread_main(void* arg) {
    print_ids("work thread");
    return NULL;
}

int main() {
    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread_main, NULL);
    if(err != 0) {
        printf("can't create thread: %s\n", strerror(err));
    }
    print_ids("main thread");
    pthread_join(tid, NULL);
    return 0;
}
