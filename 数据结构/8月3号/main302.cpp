#include <cstdio>
int main()
{
	int N,i;
	scanf("%d",&N);
	if(N==1)
	{
		printf("1/1");
		return 0;
	}
	for(i=1;N>0;i++)
		N-=i;
	i--;
	N+=i;
	if(i%2==0)
	{
		if(N==1)
			printf("1/%d",i);
		else if(N==i)
			printf("%d/1",N/1);
		else
			printf("%d/%d",N,(i-(N-1)));
	}
	else if(i%2==1)
	{
		if(N==1)
			printf("%d/1",i);
		else if(N==i)
			printf("1/%d",i);
		else
			printf("%d/%d",(i-(N-1)),N);		
	}
	return 0;
}
