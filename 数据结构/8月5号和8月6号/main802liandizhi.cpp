#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#define MAXSIZE 15
using namespace std;
typedef struct HNode{
    int data;
    struct HNode *next;
}HNode;
void Init(HNode *HashLink[])
{
    int i;
    for(i=0;i<MAXSIZE;i++)
    {
	    HashLink[i]=(HNode*)malloc(sizeof(HNode));
		HashLink[i]->next=NULL;
	}
}
void InsertHash(HNode *HashLink[],int key,int p)
{
    int k;
    HNode *q,*s;
    k=key%p;
    q=HashLink[k];
    s=new HNode;
    s->data=key;
	s->next=NULL;
    if(HashLink[k]->next==NULL)
    {
        HashLink[k]->next=s;
        cout<<"该位置插入首个值成功"<<endl;
    }
    else
    {
        while(q->next!=NULL)
            q=q->next;
        q->next=s;
        cout<<"插入单链表成功"<<endl;
    }
    return;
}
int FindHash(HNode *HashLink[],int key,int p)
{
    int k;
    HNode *q;
    k=key%p;
    q=HashLink[k];
    if(q->next==NULL)
        cout<<"该哈希表中无该数"<<endl;
    else
    {
        q=q->next;
		while(q!=NULL)
        {
            if(q->data==key)
            {
                cout<<"该数在哈希表中，位置为:"<<endl;
                return k;
            }
            else
                q=q->next;
        }
    }
    return 0;
}
int main()
{
    HNode *HashLink[MAXSIZE];
    int n,num,k;
    int p=11;
    Init(HashLink);
    cout<<"初始化成功"<<endl; 
    cout<<"请输入数据个数："<<endl;
    cin>>n;
    cout<<"请输入各个数据，以空格间隔："<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        InsertHash(HashLink,num,p);
    }
    cout<<"请输入你想查找的数："<<endl;
    cin>>num;
    k=FindHash(HashLink,num,p);
    if(k!=0)
        cout<<k<<endl;
    return 0;
}

