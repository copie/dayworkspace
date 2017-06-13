#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int a,b,c;
    cin>>a>>b>>c;
    cout<<max(a+b*c,max(a*(b+c),max(a*b*c,max((a+b)*c,a+b+c))))<<endl;
    return 0;
}