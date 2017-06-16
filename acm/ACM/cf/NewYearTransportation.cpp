#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int m;
    cin >> m;
    int x;
    x = 1;
    for(int i = 1; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if(i==x)
        {
            x=i+tmp;
        }
        if(x==m)
        {
            cout<<"YES"<<endl;
            return 0;
        }
    }
    cout<<"NO"<<endl;
    return 0;
}