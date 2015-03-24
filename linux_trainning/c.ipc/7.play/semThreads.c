#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void  print();
void  *thread_function(void *arg);
sem_t *sem;

int main(int argc,char * argv[])
{
    int n=0;
    pthread_t tid[5];
    if(argc != 2)
    {
        printf("Usage:%s name. \n",argv[0]);
        exit(0);
    }
    //init semaphore
    sem=sem_open(argv[1],O_CREAT,0644,3);

    while(n<5)
    {
        if((pthread_create(&tid[n],NULL,thread_function,NULL))!=0)
        {
            printf("can't create pthread.\n");
            exit(0);
        }
        n++;
    }
    for(n=0; n<5; n++) pthread_join(tid[n],NULL); //主线程需要等会其它线程

    int value;
    sem_getvalue(sem,&value);
    printf("Returned resource %d\n",value);

    sem_close(sem);
    sem_unlink(argv[1]);
    return 0;
}

void *thread_function(void *arg)
{
    sem_wait(sem);
    print();
    sleep(3); //因为共享段执行过快,不能达到同步效果,所以需要睡眠
    printf("\nfinish, pthread_id is %ld\n",pthread_self());
    fflush(NULL);

    sem_post(sem);
}

void print()
{
    int value;
    sem_getvalue(sem,&value);
    printf("pthread_id is %ld, get the resource, left resource is %d\n",pthread_self(),value);
}
