#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    double sum=0.0,tmp;
    for(int i=0;i<12;i++)
    {
        cin>>tmp;
        sum+=tmp;
    }
    printf("$%.2lf\n",sum/12.0);
    return 0;
}
