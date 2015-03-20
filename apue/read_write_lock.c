#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct job {
    struct job* j_next;
    struct job* j_prev;
    pthread_t j_id;
};

struct queue {
    struct job* q_head;
    struct job* q_tail;
    pthread_rwlock_t q_lock;
};

/*
 * Initialize a queue
 */
int queue_init(struct queue* job_queue) {
    job_queue->q_head = NULL;
    job_queue->q_tail = NULL;

    pthread_rwlock_init(&job_queue->q_lock, NULL);
    return 0;
}

/*
 * Insert a job at the head of the queue
 */
void job_insert(struct queue *q, struct job* j) {
    pthread_rwlock_wrlock(&q->q_lock);
    j->j_next = q->q_head;
    j->j_prev = NULL;
    if(q->q_head != NULL) {
        q->q_head->j_prev = j;
    }
    else {
        q->q_tail = j;
    }
    q->q_head = j;
    pthread_rwlock_unlock(&q->q_lock);
}

/*
 * Append a job on the tail of the queue
 */
void job_append(struct queue* q, struct job* j) {
    pthread_rwlock_wrlock(&q->q_lock);
    j->j_next = NULL;
    j->j_prev = q->q_tail;
    if(q->q_tail != NULL) {
        q->q_tail->j_next = j;
    }
    else {
        q->q_head = j;
    }
    q->q_tail = j;
    pthread_rwlock_unlock(&q->q_lock);
}

/*
 * Remove the given job from a queue
 */
void job_remove(struct queue* q, struct job* j) {
    pthread_rwlock_wrlock(&q->q_lock);
    if (j == q->q_head) {
        q->q_head = j->j_next;
        if (q->q_tail == j) {
            q->q_tail = NULL;
        }
    }
    else if (j == q->q_tail) {
        q->q_tail = j->j_prev;
        if(q->q_head == j) {
            q->q_head = NULL;
        }
    }
    else {
        j->j_prev->j_next = j->j_next;
        j->j_next->j_prev = j->j_prev;
    }

    pthread_rwlock_unlock(&q->q_lock);
}

/*
 * Find a job for the given thread ID
 */
struct job* job_find(struct queue* q, pthread_t id) {
    struct job* j = NULL;
    if (pthread_rwlock_rdlock(&q->q_lock) != 0)
        return NULL;

    for(j = q->q_head; j != NULL; j = j->j_next) {
        if (pthread_equal(j->j_id, id))
            break;
    }

    pthread_rwlock_unlock(&q->q_lock);
    return j;
}

struct job* job_init() {
    struct job* j = malloc(sizeof(struct job));
    j->j_prev = NULL;
    j->j_next = NULL;

    return j;
}

int main() {
    struct queue job_queue;
    queue_init(&job_queue);

    struct job* job1 = job_init();
    struct job* job2 = job_init();
    job_insert(&job_queue, job1);
    job_append(&job_queue, job2);
    job_remove(&job_queue, job1);
    return 0;
}
