#include <iostream>
#include <bits/stdc++.h>

using namespace std;
long long series(long long x)
{
    return x*(x+1)/2;
}
int main()

{
    long long m,b;
    cin>>m>>b;
    long long mymax=0;
    for(int i=0;i<=b;i++)
    {
        long long x=m*(b-i);
        long long t=(x+1)*series(i)+(i+1)*series(x);
        mymax = max(mymax,t);
    }
    cout<<mymax<<endl;
}