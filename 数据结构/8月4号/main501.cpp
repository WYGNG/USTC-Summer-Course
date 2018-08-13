#include <cstdio>
int main()
{
	int N;
	scanf("%d",&N);
	int a[N];
	int k=0;
	for(int i=2;i<=N;i++)
	{
		for(int j=2;j<=i;j++)
		{
			if(j!=i&&i%j==0)
				break;
			else if(j!=i&&i%j!=0)
				continue;
			else if(j==i)
			{
				a[k]=i;
				k++;
			}
		}
	}
	for(int i=0;i<k-1;i++)
	{
		for(int j=i+1;j<k;j++)
		{
			if((a[j]-a[i])<2)
				continue;
			else if((a[j]-a[i])==2)
			{
				printf("%d %d\n",a[i],a[j]);
				break;
			}
			else if((a[j]-a[i])>2)
				break;
		}
	}
	return 0;
}
