#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main()
{
    char enter;
    scanf("%c",&enter);
    enter=97+abs(122-enter);
    cout <<enter<< endl;
    return 0;
}
