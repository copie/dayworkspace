#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int x=0;
    while(n)
    {
        n--;
        x++;
        if(x%m==0)
        n++;
    }
    cout<<x<<endl;
}