#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int i;
	
    for (i = 0; i < 2; i++) {
        fork();
    }

    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    sleep(1);

    return 0;

}
