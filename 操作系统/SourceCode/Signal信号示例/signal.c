#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void alarm_handle(int);
static void sigint_handle(int);

void main(void)
{
	int p_id, pp_id;
	
	//signal(SIGHUP, SIG_IGN);
	//SIGALRM 时钟定时信号, 计算的是实际的时间或时钟时间. alarm函数使用该信号.
	signal(SIGALRM, alarm_handle);
	//SIGINT程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出，用于通知前台进程组终止进程。
	signal(SIGINT, sigint_handle);

	alarm(5);

	p_id = getpid();
	pp_id = getppid();

	printf("Process ID: %d, Parent Process ID: %d\n", p_id, pp_id);

	while(1);

	exit(0);
}

static void alarm_handle(int sig_no)
{
	printf("Recieved an alarm!\n");
	return;
}

static void sigint_handle(int sig_no)
{
	printf("\n");
	printf("DEL\n");
	exit(-1);
}

