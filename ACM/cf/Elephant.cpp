#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int x=n/5;
    if(n%5!=0)
    x++;
    cout<<x<<endl;
    return 0;
}