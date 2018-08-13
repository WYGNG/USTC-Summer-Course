#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
// 创建一个无名管道fd包含2个文件描述符的数组，fd[0]用于读，fd[1]用于写若成功返回0,否则反回-1
//一般某个进程用于读，另一个进程用于写，用于读的进程需要close(fd[1]),用于写的进程需要close(fd[0]);
int main(void)
{
    pid_t pid;
    int fd[2],i,n;
    char chr;
    pipe(fd);
    pid=fork();
    if(pid==0)          //子进程
    {
        close(fd[1]);
        for(i=0;i<10;i++)
        {
            read(fd[0],&chr,1);
            printf("Read%c\n",chr);
        }
        close(fd[0]);
        exit(0);
    }else {
        close(fd[0]);           //父进程
	for(i=0;i<10;i++)
	{
	    chr='a'+i;
	    write(fd[1],&chr,1);
	    printf("Write:%c\n",chr);
	    sleep(1);
	}
	close(fd[1]);
    }

    return 0;
}
