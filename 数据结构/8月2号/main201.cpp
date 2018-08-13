#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int yy,mm,dd;
    scanf("%d %d %d",&yy,&mm,&dd);
    if(yy<=0)
    {
        cout<<"error"<<endl;
        return 0;
    }
    if(mm>12||mm<1)
        cout<<"error"<<endl;
    else if(mm==2)
        if((yy%100!=0&&yy%4==0)||(yy%100==0&&yy%400==0))
            if(dd>29||dd<1)
            	cout<<"error"<<endl;
            else
            	cout<<"correct"<<endl;
        else if(dd>28||dd<1)
            cout<<"error"<<endl;
        else
            cout<<"correct"<<endl;
    else if(mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12)
        if(dd>31||dd<1)
            cout<<"error"<<endl;
        else
            cout<<"correct"<<endl;
    else if(mm==4||mm==6||mm==9||mm==11)
        if(dd>30||dd<1)
            cout<<"error"<<endl;
        else
            cout<<"correct"<<endl;
    return 0;
}
