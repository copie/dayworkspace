#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int ans=0;
    while(n--)
    {
        int tmp;
        cin>>tmp;
        if(tmp<=35)
        {
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}