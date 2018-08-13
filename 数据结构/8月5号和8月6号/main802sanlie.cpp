#include<iostream>
#include<cstdio>
using namespace std;
void Hashsort(int table[],int x,int p)
{
    int no=x%p;
    while(table[no]!=0)
        no=(no+1)%15;
    table[no]=x;
    return;
}
int Hashsearch(int table[],int x,int p)
{
    int no=x%p;
    int count=0;
    while(table[no]!=x&&count<15)
    {
        no=(no+1)%15;
        count++;
    }
    if(count<15)
        return no;
    else
    {
        cout<<"表中无该值"<<endl;
        return 0;
    }
}
int main()
{
    int Table[15]={0};
    int n,num;
    int p=11;
    int weizhi;
    cout<<"请输入数据个数："<<endl;
    cin>>n;
    cout<<"请输入各个数据，以空格间隔:"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        Hashsort(Table,num,p);
    }
    cout<<"哈希查找表已建好"<<endl;
    cout<<"请输入希望查找的数据值:"<<endl;
    cin>>num;
    weizhi=Hashsearch(Table,num,p);
    cout<<"该数据在下标"<<weizhi<<"处"<<endl;
    return 0;
}
