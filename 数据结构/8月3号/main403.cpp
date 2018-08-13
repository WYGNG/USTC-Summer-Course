#include <cstdio>
int main()
{
	int N,temp;
	scanf("%d",&N);
	int a[N+2];
	for(int i=0;i<N;i++)
		scanf("%d",&a[i]);
	for(int j=0;j<N;j++)
	{
		for(int k=j+1;k<N;k++)
		{
			if(a[j]>a[k])
			{
				temp=a[j];
				a[j]=a[k];
				a[k]=temp;
			}
		}
	}
	for(int m=0;m<N;m++)
		printf("%d ",a[m]);
	printf("\n");
	scanf("%d",&a[N]);
	for(int i=0;i<N;i++)
	{
		int temp;
		if(a[i]>a[N])
		{
			for(int j=N-1;j>=i;j--)
			{
				temp=a[j+1];
				a[j+1]=a[j];
				a[j]=temp;	
			}
		}
	}
	for(int m=0;m<=N;m++)
		printf("%d ",a[m]);
	printf("\n");
	return 0;	
}

