#include <cstdio>  
using namespace std;  
int sum=0;  
void digui(int a,int b)  
{  
    for(int i=a;i<b;i++)  
    {  
        if(b%i==0&&i<=b/i)  
        {  
            sum++;  
            digui(i,b/i);
        }  
        if(i>b/i) 
			break;  
    }  
}  
int main()  
{   
    int a;  
    scanf("%d",&a);  
    digui(2,a);  
    printf("%d",sum);   
    return 0;  
}













