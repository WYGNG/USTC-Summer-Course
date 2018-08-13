/*
进程调度算法采用最大优先数优先的调度算法和先来先服务算法。每个进程有一个进程控制
块（PCB）表示。进程控制块可以包含如下信息：进程名、优先数、到达时间、需要运行时间、
已用CPU时间、进程状态等等。进程的优先数及需要的运行时间可以事先人为地指定（也可以由
随机数产生）。进程的到达时间为进程输入的时间。
进程的运行时间以时间片为单位进行计算。
每个进程的状态可以是就绪 W（Wait ）、运行R（Run）、或完成F（Finish ）三种状态之一。
就绪进程获得CPU后都只能运行一个时间片。用已占用CPU时间加1来表示。
如果运行一个时间片后，进程的已占用CPU时间已达到所需要的运行时间，则撤消该进程；
如果运行一个时间片后进程的已占用CPU时间还未达所需要的运行时间，也就是进程还需要
继续运行，此时应将进程的优先数减1（即降低一级），然后把它插入就绪队列等待CPU。
每进行一次调度程序都打印一次运行进程、就绪队列、以及各个进程的PCB，以便进行检查。
重复以上过程，直到所要进程都完成为止。
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef struct PCB{ 
	char state;
	int id;	
	int super;
	int arrivetime;
	int runtime;
	struct PCB *next;
}PCB;
void insertjincheng(PCB *root,PCB *q){
	PCB *temp=root;
	if(temp->next==NULL)
	{
		temp->next=q;
		return;
	}
	while(temp->next!=NULL&&temp->arrivetime<q->arrivetime)
		temp=temp->next;
	while(temp->super>q->super&&temp->next!=NULL)
		temp=temp->next;
	q->next=temp->next;
	temp->next=q;
	return;		
} 
void yunxing(PCB *&root){
	PCB *temp=root;
	if(temp->next==NULL)
	{
		printf("所有进程运行结束\n");
		return;
	}
	temp=temp->next;
	printf("现在运行%d号进程\n",temp->id);
	temp->super-=1;
	temp->runtime-=1;
	printf("%d号进程时间片用完\n",temp->id);
	if(temp->runtime==0){
		temp->state='R';
		printf("编号为%d的进程运行结束,进程状态为%c\n",temp->id,temp->state);
		root->next=temp->next;
		free(temp);
	}
	else{
		root->next=temp->next;
		insertjincheng(root,temp);
	}
	return;
}
int main(){	
	PCB *root=(PCB*)malloc(sizeof(PCB));
	root->next=NULL;
	int num;
	printf("请输入进程总数量：\n");
	scanf("%d",&num);
	printf("请输入各个进程的信息：\n");
	for(int i=0;i<num;i++){
		PCB *q=(PCB*)malloc(sizeof(PCB));
		PCB *p=root;
		q->state='W';
		q->next=NULL;
		printf("\n请输入进程编号、进程初始优先级、进程到达时间、进程运行时间，以空格间隔：\n");
		cin>>q->id>>q->super>>q->arrivetime>>q->runtime;
		printf("输入%d号进程信息成功\n",q->id);
		insertjincheng(root,q);
		printf("插入%d号进程到就绪队列中成功\n",q->id);
	}
	printf("输入完成\n");
	while(root->next!=NULL){
		yunxing(root);
		printf("进程运行了一次\n");
	} 	
	return 0;
}
	
	
	
