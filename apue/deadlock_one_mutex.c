#include <stdio.h>
#include <pthread.h>

int main() {
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    printf("lock for the first time\n");
    pthread_mutex_lock(&lock);
    /* Lock twice, thus it is a deadlock */
    printf("lock for the second time\n");
    pthread_mutex_lock(&lock);
    printf("Never reach here!\n");
    return 0;
}
