#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

#define SEM_NAME "name"

int main()
{
    sem_t *sem_test;

    sem_test = sem_open("ni",0);

    if(sem_test < 0)
    {
        printf("B进程创建信号量失败！errno=%d\n",errno);
        exit(-1);
    }

    printf("B\n");
    sem_post(sem_test);
    printf("B进程执行完毕！\n");
    sem_close(sem_test);
    sem_unlink("ni");
    return 0;
}
