#include <cstdio>
int main()
{
	int N;
	double sum=0,ave=0;
	scanf("%d",&N);
	int a[N+1];
	for(int i=0;i<N;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	ave=sum/N;
	for(int j=0;j<N;j++)
	{
		if(a[j]>ave)
			printf("%d ",a[j]);
	}
	return 0;
}

