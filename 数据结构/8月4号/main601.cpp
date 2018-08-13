#include<stdio.h>
#include<malloc.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node;
int main()
{
	Node *LA=(Node*)malloc(sizeof(Node));
	LA->next = NULL;
	Node *LB=(Node*)malloc(sizeof(Node));
	LB->next = NULL;
	int N;
	scanf("%d", &N);
	for(int i=0;i<N;i++)
	{
		Node *temp=(Node*)malloc(sizeof(Node));
		scanf("%d",&temp->data);
		Node *p;
		if(temp->data%2==1)
    	{
    		p=LA;
			while(p->next!=NULL && p->next->data<temp->data)
				p=p->next;
			temp->next = p->next;
			p->next = temp;
		}
		else
		{
			p=LB;
			while(p->next!=NULL && p->next->data<temp->data)
				p=p->next;
			temp->next = p->next;
			p->next = temp;
		}
	}
	Node *s=LA->next;
	while(s!=NULL)
	{
		printf("%d ", s->data);
		s=s->next;
	}
	s=LB->next;
	while(s!=NULL)
	{
		printf("%d ", s->data);
		s=s->next;
	}
	return 0;
}
