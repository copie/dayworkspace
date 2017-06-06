#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        double a,b;
        cin>>a>>b;
        cout<<"Property "<<i<<": This property will begin eroding in year "<<ceil((a*a+b*b)*3.1415926535/100)<<"."<<endl;
    }
    cout<<"END OF OUTPUT."<<endl;
}