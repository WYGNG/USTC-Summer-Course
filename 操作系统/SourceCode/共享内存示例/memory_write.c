#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sem.h>
/*
int shmget(key_t key, size_t size, int shmflg); 申请共享内存
        错误码：
            EINVAL：参数size小于SHMMIN或大于SHMMAX
            EEXIST：预建立key所指的共享内存，但已经存在
            EIDRM：参数key所指的共享内存已经删除
            ENOSPC：超过了系统允许建立的共享内存的最大值(SHMALL)
            ENOENT：参数key所指的共享内存不存在，而参数shmflg未设IPC_CREAT位
            EACCES：没有权限
            ENOMEM：核心内存不足
void *shmat(int shmid, const void *shmaddr, int shmflg);
        参数解释：
            shmid ：  共享内存标识符 
            shmaddr ：指定共享内存出现在进程内存地址的什么位置，直接指定为NULL让内核自己决定一个合适的地址位置 
            shmflg：SHM_RDONLY：为只读模式，其他为读写模式  
int shmdt(const void *shmaddr);  
            shmaddr：连接的共享内存的起始地址
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
        cmd参数说明：
            IPC_STAT：得到共享内存的状态，把共享内存的shmid_ds结构复制到buf中
            IPC_SET：改变共享内存的状态，把buf所指的shmid_ds结构中的uid、gid、mode复制到共享内存的shmid_ds结构内
            IPC_RMID：删除这片共享内存

*/

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

    /** step4 对该共享指针进行操作,给共享指针赋值 */
    strncpy(pchShm,"hello ustc",20);

    /* step5 释放该共享地址 */
    shmdt(pchShm);

    /** 删除该块共享内存 */
    //shmctl(nShmid,IPC_RMID,NULL);

    return 0;
} 

