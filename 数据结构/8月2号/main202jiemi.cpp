#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int number,temp;
    int a[4];
    scanf("%d",&number);
    if(number>9999||number<1000)
    {
        printf("error");
        return 0;
    }
    for(int i=0;i<4;i++)
    {
    	a[i]=number%10;
    	number=number/10;
    }
    for(int i=0;i<4;i++)
        if(a[i]>=7)
            a[i]=a[i]-7;
        else
            a[i]=a[i]+10-7;
    temp=a[2];
    a[2]=a[0];
    a[0]=temp;
    temp=a[3];
    a[3]=a[1];
    a[1]=temp;
    for(int i=0;i<4;i++)
        printf("%d",a[i]);
    return 0;
}
