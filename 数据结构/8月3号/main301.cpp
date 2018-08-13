#include <cstdio>
int main()
{
	int a[10];
	scanf("%d",&a[0]);
	int i=1;
	while(i<=9)
	{
		a[i]=(a[i-1]+1)*2;
		i++;
	}
	printf("%d",a[9]);
	return 0;	
}
