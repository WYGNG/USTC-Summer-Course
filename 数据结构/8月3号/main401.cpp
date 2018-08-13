#include <cstdio>
#include <cstring>
int main()
{
	char a[101];
	int count=0,length=0;
	gets(a);
	length=strlen(a);
	int i=0;
	while(a[i]==32)
	{
		i++;
	}
	for(;i<=length;i++)
	{
		if(a[i]==32||a[i]=='\0')
			count++;
	}
	printf("%d",count);
	return 0;
}
