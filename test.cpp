#include <bits/stdc++.h>
#define mod 1000000009
typedef long long LL;

using namespace std;

int a[100005], b[100005], vis[1000005];
vector<int> fac[10000005];

void get_fac()
{
    for (int i = 1; i <= 1000005; i++)
    {
        for (int j = i; j <= 1000005; j += i)
            fac[j].push_back(i);
    }
}
int dfs(int aa[], int n)
{
    if (vis[n])
        return 0;
    vis[n] = 1;
    return dfs(aa, aa[n]) + 1;
}
int main()
{
    int n, m, c = 1;
    get_fac();
    while (~scanf("%d %d", &n, &m))
    {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = 0; i < m; i++)
            scanf("%d", &b[i]);
        vector<int> A;
        int B[100005];
        memset(B, 0, sizeof(B));
        for (int i = 0; i < n; i++)
            if (!vis[i])
                A.push_back(dfs(a, i));
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < m; i++)
            if (!vis[i])
                B[dfs(b, i)]++;
        int la, lb, len;
        LL ans = 1;
        for (int i = 0; i < A.size(); i++)
        {
            la = A[i];
            LL temp = 0;
            len = fac[la].size();
            for (int j = 0; j < len; j++)
            {
                lb = fac[la][j];
                temp = (temp + lb * B[lb]) % mod;
            }
            ans = (ans * temp) % mod;
        }
        printf("Case #%d: %lld\n", c++, ans);
    }
    return 0;
}