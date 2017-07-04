#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int a, b;
    cin >> a >> b;
    a = min(a, b);
    int ans = 1;
    for (int i = 1; i <=a;i++)
    {
        ans*=i;
    }
    cout<<ans<<endl;
    return 0;
}