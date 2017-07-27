#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    double n;
    while(cin>>n,n)
    {
        double sum = 0;
        int x;
        for(double i=2;sum<n;i++)
        {
           
            sum=sum+1.0/i;
            x=i;
            
        }
        cout<<x-1<<" card(s)"<<endl;
    }
}