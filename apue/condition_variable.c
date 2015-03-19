#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct msg {
    struct msg* m_next;
    int msg_id;
};

struct msg* work_queue;
pthread_cond_t queue_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

void consume_msg() {
    struct msg* m;
    while(1) {
        pthread_mutex_lock(&queue_lock);
        while(work_queue == NULL)
            pthread_cond_wait(&queue_ready, &queue_lock);
        m = work_queue;
        work_queue = m->m_next;
        pthread_mutex_unlock(&queue_lock);
        printf("msg_id:%d consumed\n", m->msg_id);
        free(m);
    }
}

void produce_msg(struct msg* m) {
    pthread_mutex_lock(&queue_lock);
    m->m_next = work_queue;
    work_queue = m;
    pthread_mutex_unlock(&queue_lock);
    pthread_cond_signal(&queue_ready);
}

void* producer(void* arg) {
    printf("produer started\n");
    for(int i = 0; i < 10; i++) {
        struct msg* m = (struct msg*)malloc(sizeof(struct msg));
        m->msg_id = i;
        produce_msg(m);
    }
    return NULL;
}

void* consumer(void* arg) {
    printf("consumer started\n");
    consume_msg();
    return NULL;
}

int main() {
    pthread_t tp, tc;
    pthread_create(&tp, NULL, producer, NULL);
    pthread_create(&tc, NULL, consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    return 0;
}
