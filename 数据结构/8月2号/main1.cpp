#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    long long time;
    int dd,hh,mm,ss;
    scanf("%lld",&time);
    dd=time/(3600*24);
    hh=(time-dd*3600*24)/3600;
    mm=(time-dd*3600*24-hh*3600)/60;
    ss=time-dd*3600*24-hh*3600-mm*60;
    cout <<dd<<":"<<hh<<":"<<mm<<":"<<ss<<endl;
    return 0;
}
