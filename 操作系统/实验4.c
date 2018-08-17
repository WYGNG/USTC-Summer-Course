//请在linux中运行该代码，linux中要安装gcc，版本不低于4.8.4
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void main( ){
	int pchild1,pchild2;
	int a[2];
	char output[50],input[50];
	pipe(a);
	while ((pchild1=fork())==-1)
		printf("fork创建子进程1失败，重新创建中\n");
	printf("%d\n",pchild1);
	if(pchild1==0){
		lockf(a[1],1,0);
		sprintf(output,"子进程1发来信息!\n");
		printf("%d\n",pchild1);
		write(a[1],output,50);
		sleep(3);
		lockf(a[1],0,0);
		exit(0);
	}
	else{
		while((pchild2=fork())==-1);
			printf("fork创建子进程2失败，重新创建中\n");
		printf("%d\n",pchild2);
		if(pchild2==0){
			lockf(a[1],1,0);
			sprintf(output,"子进程2发来信息!\n");
			printf("%d\n",pchild2);
			write(a[1],output,50);
			sleep(3);
			lockf(a[1],0,0);
			exit(0);
		}
		else{
			waitpid(pchild1);
			read(a[0],input,50);
			printf("%s\n",input);
			waitpid(pchild2);
			read(a[0],input,50);
			printf("%s\n",input);
			exit(0);
		}
	}
}
