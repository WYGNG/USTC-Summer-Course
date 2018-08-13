#include <cstdio>
int main()
{
	int N;
	scanf("%d",&N);
	int count=1;
	printf("1 ");
	for(int i=2;i<=N;i++)
	{
		int num=0;
		for(int j=1;j<=i/2;j++)
		{
			if(i%j==0)
				num+=j;
		}
		if(num==i)
		{
			printf("%d ",i);
			count++;
			if(count%5==0)
				printf("\n");
		}
	}
	return 0;
}
