//clientA
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
 
#define N 64
#define TYPEA 100
#define TYPEB 200
 
typedef struct
{
	long   mtype;       /* Message type. */
	char   mtext[N];    /* Message text. */
}MSGBUF;
 
#define LEN (sizeof(MSGBUF)-sizeof(long))
 
int main()
{
	key_t key;
	int msgid;
	MSGBUF buf;
    pid_t pid;
 
	if ((key = ftok(".", 'a')) == -1)
	{
		perror("ftok");
		exit(-1);
	}
	
	if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1)
	{
		perror("msgget");
		exit(-1);
	}
 
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(-1);
    }
 
    if (pid == 0)//send
    {
        while (1)
        {
    	    if (fgets(buf.mtext, N, stdin) == NULL)
    	    {
	    	    perror("fgets");
    	    	exit(-1);
    	    }
        	buf.mtext[strlen(buf.mtext)-1] = '\0';
            buf.mtype = TYPEB;
 
    	    if (msgsnd(msgid, (void *)&buf, LEN, 0) == -1)
        	{
	        	perror("msgsnd");
		        exit(-1);
        	}	
 
            if (strncmp(buf.mtext, "quit", 4) == 0)
            {
	            if (msgctl(msgid, IPC_RMID, NULL) == -1)
            	{
            		perror("msgctl");
            		exit(-1);
            	}
                kill(getppid(), SIGUSR1);
                exit(0);
            }
        }
    }
    else//recv
    {
        while (1)
        {
	        if (msgrcv(msgid, &buf, LEN, TYPEA, 0) == -1)
        	{
	        	perror("msgrcfv");
		        exit(-1);
        	}
 
	        printf("%s\n", buf.mtext);
            if (strncmp(buf.mtext, "quit", 4) == 0)
            {
                kill(pid, SIGUSR1);
                exit(0);
            }
        }
    }
 
	exit(0);
}

