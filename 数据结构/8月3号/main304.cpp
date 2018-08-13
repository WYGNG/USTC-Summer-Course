#include <cstdio>
int main()
{
	int yy,mm,dd;
	int day=0;
	scanf("%d %d %d",&yy,&mm,&dd);
	for(int i=1;i<=mm;i++)
	{
		if(i==mm)
		{
			day+=dd;
			printf("%d",day);
			return 0;
		}
		else if(i<mm)
		{
			if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
				day+=31;
			else if(i==2)
				if((yy%4==0&&yy%100!=0)||(yy%100==0&&yy%400==0))
					day+=29;
				else 
					day+=28;
			else if(i==4||i==6||i==9||i==11)
					day+=30;
		}
	}
	return 0;
}
