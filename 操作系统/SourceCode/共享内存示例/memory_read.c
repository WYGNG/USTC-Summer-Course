#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sem.h>


#define PRI_SHM_ID 1000
#define PATH_SHM "/home/zhu/"


int main()
{
    key_t keyVal = 0;
    int nShmid = 0;
    char *pchShm = NULL;


    /* step 1 获得key值 */
    keyVal = ftok(PATH_SHM,PRI_SHM_ID);

    /** step 2 申请共享内存 */
    nShmid = shmget(keyVal,10,IPC_CREAT|0666);
    if(nShmid == -1)
    {
        printf("create share memory failed\n");
        return 1;
    }

    /**step3 申请共享内存指针 */
    pchShm = (char*)shmat(nShmid,0,0);
    if(NULL == pchShm)
    {
        printf("get share pointer failed\n");
        return 1;
    }

    /** step4 对该共享指针进行操作 */
    printf("%s\n",pchShm);

    /* step5 释放该共享地址 */
    shmdt(pchShm);

    /** 删除该块共享内存,一般情况下不要删除该共享内存 */
    //shmctl(nShmid,IPC_RMID,NULL);

    return 0;
} 
