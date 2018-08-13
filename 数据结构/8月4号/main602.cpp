#include<cstdio>
#include<cstdlib>
typedef struct Node
{
    int num;
    struct Node *next;
}LinkList;
LinkList *creatlist(int n)
{
    LinkList *p,*q,*head;
    int i=1;
    p=(LinkList*)malloc(sizeof(LinkList));
    p->num=i;
    head=p;
    for(i=2;i<=n;i++)
    {
        q=(LinkList*)malloc(sizeof(LinkList)); 
        q->num=i;
        p->next=q;
        p=q;
    }
    p->next=head;        
    return head;
}
void chulie(LinkList *L,int m,int k)
{
    int i;
    LinkList *p, *s, *q;
    p=L;
    for(int i=1;i<k;i++)
    	p=p->next;
    while(p->next!=p)
    {
        for(i=1;i<m;i++) 
        {
            q=p;
            p=p->next;
        }
        printf("%d ",p->num);
        s=p;
        q->next=p->next;
        p=p->next; 
        free(s);
    }
    printf("%d\n", p->num);
}
int main()
{
    LinkList *L;
    int n,k,m;
    scanf("%d %d %d",&n,&k,&m);
    L=creatlist(n);
    chulie(L,m,k);
    return 0;
}
