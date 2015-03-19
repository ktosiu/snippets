#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

struct resource {
    int ref_count;
    pthread_mutex_t lock;
    /*...*/
};

struct resource* resource_alloc() {
    struct resource* p = (struct resource*)malloc(sizeof(struct resource));
    assert(p != NULL);
    p->ref_count = 1;
    if(pthread_mutex_init(&p->lock, NULL) != 0) {
        free(p);
        return NULL;
    }
    return p;
}

void resource_hold(struct resource* p) {
    pthread_mutex_lock(&p->lock);
    p->ref_count++;
    pthread_mutex_unlock(&p->lock);
}

void resource_release(struct resource* p) {
    pthread_mutex_lock(&p->lock);
    p->ref_count--;
    if(p->ref_count == 0) {
        pthread_mutex_unlock(&p->lock);
        pthread_mutex_destroy(&p->lock);
        free(p);
        printf("free resource!\n");
    }
    else {
        pthread_mutex_unlock(&p->lock);
    }
}

int main() {
    struct resource* res = resource_alloc();
    resource_hold(res);
    resource_release(res);
    resource_release(res);
    return 0;
}
