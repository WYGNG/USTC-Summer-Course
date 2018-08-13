#include <iostream>
#include <cstdio>
#include <cmath>
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
        a[i]=(a[i]+7)%10;
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
