//请在linux系统中运行该代码，linux系统中要安装g++，版本不低于4.8.5
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#define NUM 10  //要访问的页面的个数
#define M 4      //物理块的个数
using namespace std;
typedef struct BLOCK{
	int page;
	int tm;
}BLOCK;
BLOCK PB[M];
int PAGE[NUM];
int RESULT[M][NUM];
void INIT(BLOCK PB[M],int RESULT[M][NUM]){//初始化PB和RESULT数组
	printf("开始初始化PB和RESULT数组\n");
	for(int k=0;k<M;k++){
		PB[k].page=-1;
		PB[k].tm=-1;
	}
	for(int i=0;i<M;i++){
		for(int j=0;j<NUM;j++)
			RESULT[i][j]=-1;
	}
	printf("PB和RESULT数组初始化完成\n");
	return;
}
void RANDOMPAGE(int PAGE[NUM]){//初始化并生成随机页面请求序列
	printf("开始初始化随机页面请求序列\n");
	for(int i=0;i<NUM;i++)
		PAGE[i]=-1;
	printf("随机页面请求序列初始化完成\n");
	printf("开始生成随机页面请求序列\n");
	for(int j=0;j<NUM;j++){
		srand((unsigned)time(NULL));
		PAGE[j]=(rand()%10);
		sleep(rand()%2+1);
	}
	printf("打印生成的随机请求序列\n");
	for(int m=0;m<NUM;m++)
		printf("%d ",PAGE[m]);
	printf("\n");
	printf("生成的随机请求序列打印完成\n");
	return;
}
void PRINTRESULT(int RESULT[M][NUM],int PAGE[NUM]){//打印RESULT数组
    printf("开始打印算法置换后的结果\n");
    printf("随机生成的页面请求序列及算法处理过程为:\n");
	for(int i=0;i<NUM;i++){
    	printf("%d  ",PAGE[i]);
    }
    printf("\n");
	for(int j=0;j<M;j++){
    	for(int k=0;k<NUM;k++){
      		printf("%d  ",RESULT[j][k]);
    	}
      	printf("\n");
    }
    printf("算法置换后的结果打印完成\n");
    return;
}
void LRUTIME(BLOCK PB[M]){//对LRU算法中页面置换或使用后各块的停留时间的处理
	for(int i=0;i<M;i++){
		if(PB[i].page!=-1)
			PB[i].tm+=1;
	}
	return;
}
int FIFOINSERT(int temp1,BLOCK PB[M],int PAGE[NUM],int *&p1){//页在物理块中使用FIFO算法查找或置换
	for(int k=0;k<M;k++){
		if(PB[k].page==-1){
			PB[k].page=temp1;
			PB[k].tm=0;
			LRUTIME(PB);
			*p1+=1;
			printf("缺页数+1\n");
			return k;
		}
	}
	for(int j=0;j<M;j++){
		if(PB[j].page==temp1){
			LRUTIME(PB);
			return j;
		}
	}
	int temp;
	int flag;
	temp=PB[0].tm;
	flag=0;
	for(int n=0;n<M;n++){
		if(PB[n].tm>temp){
			temp=PB[n].tm;
			flag=n;
		}
	}
	*p1+=1;
	printf("缺页数+1\n");
	PB[flag].page=temp1;
	PB[flag].tm=0;
	LRUTIME(PB);
	return flag;
}
void FIFORESULT(int RESULT[M][NUM],int PAGE[NUM],int *&p1,double *&p2){//保存并打印FIFO算法置换后的结果
	printf("开始用FIFO算法置换并记录结果\n");
	for(int i=0;i<NUM;i++){
		int temp1,temp2;
		temp1=PAGE[i];
		temp2=FIFOINSERT(temp1,PB,PAGE,p1);
		RESULT[temp2][i]=temp1;
		for(int j=i;j<NUM;j++)
			RESULT[temp2][j]=temp1;
	}
	*p2=((double)*p1)/NUM;
	printf("FIFO算法置换结果记录完成\n");
	PRINTRESULT(RESULT,PAGE);
	printf("FIFO算法的缺页次数为：%d\n",*p1);
	printf("FIFO算法的缺页率为：%.4lf\n",*p2);
	return;
}
int LRUINSERT(int temp1,BLOCK PB[M],int PAGE[NUM],int *&p1){//单个页号在物理块中使用LRU算法查找或置换
	for(int j=0;j<M;j++){
		if(PB[j].page==-1){
			PB[j].page=temp1;
			PB[j].tm=0;
			*p1+=1;
			printf("缺页数+1\n");
			LRUTIME(PB);
			return j;
		}
	}
	for(int k=0;k<M;k++){
		if(PB[k].page==temp1){
			PB[k].tm=0;
			LRUTIME(PB);
			return k;
		}
	}
	int temp;
	int flag;
	temp=PB[0].tm;
	flag=0;
	for(int m=1;m<M;m++){
		if(PB[m].tm>temp){
			temp=PB[m].tm;
			flag=m;
		}
	}
	PB[flag].page=temp1;
	PB[flag].tm=0;
	*p1+=1;
	printf("缺页数+1\n");
	LRUTIME(PB);
	return flag;
}
void LRURESULT(int RESULT[M][NUM],int PAGE[NUM],int *&p1,double *&p2){//保存并打印LRU算法置换后的结果
	printf("开始用LRU算法置换并记录结果\n");
	for(int i=0;i<NUM;i++){
		int temp1,temp2;
		temp1=PAGE[i];
		temp2=LRUINSERT(temp1,PB,PAGE,p1);
		RESULT[temp2][i]=temp1;
		for(int j=i;j<NUM;j++)
			RESULT[temp2][j]=temp1;
	}
	*p2=((double)*p1)/NUM;
	PRINTRESULT(RESULT,PAGE);
	printf("LRU算法的缺页次数为：%d\n",*p1);
	printf("LRU算法的缺页率为：%.4lf\n",*p2);
	printf("LRU算法置换结果记录完成\n");
	return;
}
int main(){
	int QUEYESHU=0;
	double QUEYELV=0;
	int status;
	int *p1=&QUEYESHU;
	double *p2=&QUEYELV;
	int pchild1,pchild2;
	while ((pchild1=fork())==-1)
		printf("fork创建子进程1失败，重新创建中\n");
	printf("子进程1序号为%d\n",pchild1);
	if(pchild1==0){
		printf("子进程1创建成功\n");
		INIT(PB,RESULT);
		RANDOMPAGE(PAGE);
		FIFORESULT(RESULT,PAGE,p1,p2);
		printf("子进程1执行完毕\n");
		exit(0);
	}
	else{
		waitpid(pchild1,&status,0);
		while((pchild2=fork())==-1)
			printf("fork创建子进程2失败，重新创建中\n");
		printf("子进程2序号为%d\n",pchild2);
		if(pchild2==0){
			printf("子进程2创建成功\n");
			INIT(PB,RESULT);
			RANDOMPAGE(PAGE);
			LRURESULT(RESULT,PAGE,p1,p2);
			printf("子进程2执行完毕\n");
			exit(0);
		}
		else{
			waitpid(pchild2,&status,0);
			printf("主进程执行完毕\n");
			exit(0);
		}
	}
	return 0;
}
