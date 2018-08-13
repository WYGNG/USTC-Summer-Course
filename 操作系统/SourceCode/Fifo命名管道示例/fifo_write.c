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
    int fifoid = -1;

    char buffer[BUF_LEN] = { 0 };

    if (access(FIFO_NAME, F_OK) < 0){
        fifoid = mkfifo(FIFO_NAME, 0777);
        if (fifoid < 0){
            perror("mkfifo error\n");
            return -1;
        }
    }

    pipeid = open(FIFO_NAME, O_WRONLY);
    if (pipeid < 0){
        perror("open pipeid error\n");
        return -1;
    }

    int read_bytes = read(STDIN_FILENO, buffer, BUF_LEN);
    if (read_bytes < 0){
        perror("read error\n");
        close(pipeid);
        return -1;
    }

    const char * buff_send = buffer;
    int no_write_bytes = read_bytes;
    while (no_write_bytes > 0){
        int n = write(pipeid, buff_send, no_write_bytes);
        if (n < 0){
            perror("write error\n");
            close(pipeid);
            return -1;
        }

        no_write_bytes -= n;
        buff_send += n;
    }

    close(pipeid);

    return 0;
}
