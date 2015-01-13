#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void  print();
sem_t *sem;                                                                                                    

int main(int argc,char * argv[])
{
    int n=0,j;
    pid_t pid;
    if(argc != 2)
    {
        printf("Usage:%s name.\n",argv[0]);
        exit(0);
    }

    //该信号灯不会因为不同进程而不同。
    sem=sem_open(argv[1],O_CREAT,0644,3);
    while(n<5)
    {
        pid = fork();
        if(pid == 0)
        {
            sem_wait(sem);
            print();
            sleep(3);
            printf("\nfinish,the pid is %d\n",getpid());
            fflush(NULL);

            sem_post(sem);
            exit(0);
        }
        n++;
    }

    j=0;
    //等待所有子进程退出
    while(j<5)
    {
        wait(NULL);
        j++;
    }

    int value;
    sem_getvalue(sem,&value);
    printf("Returned resource %d\n",value);

    sem_close(sem);
    sem_unlink(argv[1]);
    return 0;
}

void print()
{
    int value;
    sem_getvalue(sem,&value);
    printf("pid is %d, get the resource, left resource is %d\n",getpid(),value);
}
