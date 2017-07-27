#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int a[1000];
    int x = 0;
    int y = 0;
    int tmp1;
    int tmp2;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(a[i]%2==0)
        {
            x++;
            tmp1=i;
        }
        else
        {
            y++;
            tmp2=i;
        }
    }
    if(x==1)
        cout<<tmp1<<endl;
    else
        cout<<tmp2<<endl;
    return 0;
}