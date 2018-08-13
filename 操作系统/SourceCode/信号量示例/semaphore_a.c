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
	sem_test = sem_open("ni", O_CREAT, 0644, 0);
	if(sem_test < 0)
	{
		printf("A进程创建信号量失败！errno=%d\n",errno);
		exit(-1);
	}
	printf("进程A进入等待……\n");
	printf("A\n");
	sem_wait(sem_test);
	printf("C\n");
	sem_post(sem_test);
	printf("A进程执行完毕！\n");
	sem_close(sem_test);
	sem_unlink("ni");
	return 0;
}
