#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_NAME "/var/tmp/fifo_test"
#define BUF_LEN PIPE_BUF


int main(int argc, char *argv[])
{
    int pipeid = -1;

    char buffer[BUF_LEN] = { 0 };

    pipeid = open(FIFO_NAME, O_RDONLY);

    int n = read(pipeid, buffer, BUF_LEN - 1);
    if (n < 0){
        perror("read error\n");
        close(pipeid);
        return -1;
    }

    write(STDOUT_FILENO, buffer, n);

    close(pipeid);

    return 0;
}
