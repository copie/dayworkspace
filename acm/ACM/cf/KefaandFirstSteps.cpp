#include <bits/stdc++.h>
#define max(a, b) a > b ? a : b
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int a[100010];
    // int dp[10000];
    int n;
    cin >> n;
    int maxx = 1;
    cin >> a[0];
    int dp = 1;
    for (int i = 1; i < n; i++)
    {

        {
            cin >> a[i];
            if (a[i] < a[i - 1])
            {
                dp = 1;
            }
            else
            {
                dp = dp + 1;
                maxx = max(maxx, dp);
            }
        }
    }
    cout << maxx << endl;
    return 0;
}
// #include <bits/stdc++.h>

// using namespace std;

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     int a[100010];
//     int dp[100010];
//     int n;
//     cin>>n;
//     int maxx=1;
//     for(int i=0;i<n;i++)
//     {
//         if(i==0)
//         {
//             cin>>a[i];
//             dp[0]=1;
//         }
//         else
//         {
//             cin>>a[i];
//             if(a[i]<a[i-1])
//             {
//                 dp[i]=1;
//             }
//             else
//             {
//                 dp[i]=dp[i-1]+1;
//                 maxx=max(maxx,dp[i]);
//             }
//         }
//     }
//     cout<<maxx<<endl;
//     return 0;
// }