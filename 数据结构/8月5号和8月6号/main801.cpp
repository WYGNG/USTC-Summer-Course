#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct BTNode{
	int key;
	BTNode *lchild,*rchild;
};
void insertBST(BTNode *&root,int x)
{
	if(root==NULL)
	{
		root=new BTNode;
		root->key=x;
		root->lchild=root->rchild=NULL;
		return;
	}
	else if(root->key>x)
		insertBST(root->lchild,x);
	else if(root->key<x)
		insertBST(root->rchild,x);
}
void searchBST(BTNode *root,int x)
{
	if(root==NULL)
	{
		cout<<"找不到此数"<<endl;
		return;
	}
	if(root->key==x)
	{
		cout<<"找到此数"<<endl;
		return;
	}
	if(root->key>x)
		searchBST(root->lchild,x);
	else if(root->key<x)
		searchBST(root->rchild,x);
}
void deleteNode(BTNode *&root,int x)
{
	if(root==NULL)
    {
        cout<<"该二叉树中没有要删除的值："<<x<<endl;
        return;
    }
    if(root->key==x)
    {
        if(root->lchild==NULL&&root->rchild==NULL)
        {
            free(root);
            cout<<"删除成功"<<endl;
        }
        else if(root->lchild!=NULL)
        {
            BTNode *temp=root->lchild;
            while(temp->rchild!=NULL)
                temp=temp->rchild;
            root->key=temp->key;
            deleteNode(root->lchild,temp->key);
        }
        else
        {
            BTNode *temp=root->rchild;
            while(temp->lchild!=NULL)
                temp=temp->lchild;
            root->key=temp->key;
            deleteNode(root->rchild,temp->key);
        }
    }
    else if(root->key>x)
        deleteNode(root->lchild,x);
    else
        deleteNode(root->rchild,x);
}
int main()
{
	BTNode *root=NULL;
	int n,num,searchnum,deletenum;
	cout<<"请输入建立二叉树的数值个数:"<<endl;
	cin>>n;
	cout<<"请依次输入数据值:"<<endl;
	for(int i=0;i<n;i++)
    {
        cin>>num;
        cout<<"第"<<i+1<<"此输入成功"<<endl;
        insertBST(root,num);
        cout<<"第"<<i+1<<"次插入成功"<<endl;
    }
    cout<<"创建二叉排序树成功"<<endl;
	cout<<"请输入要查找的数据值:"<<endl;
	cin>>searchnum;
    searchBST(root,searchnum);
	cout<<"请输入要删除的数据值:"<<endl;
	cin>>deletenum;
	deleteNode(root,deletenum);
	return 0;
}

