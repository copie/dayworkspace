#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
LL w[105][105];
int vis[105], m, n;
vector<int> y[105];
vector<pair<int, int>> C[10005];
LL calc(int col)
{
    memset(vis, 0, sizeof(vis));
    LL sum = 0;
    for (auto now : C[col])
    {
        int ni = now.first, nj = now.second;
        for (int i = 1; i <= m; i++)
        {
            y[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            if (vis[i])
                y[vis[i]].push_back(i);
        }
        int yl = 1;
        int yr = m;
        int flag = 0;
        for (int i = ni; i >= 1; i--)
        {
            vector<int>::iterator it;
            for (it = y[i].begin(); it != y[i].end(); it++)
            {
                int yy = *it;
                if (yy < nj)
                {
                    yl = max(yl, yy + 1);
                }
                else if (yy > nj)
                {
                    yr = min(yr, yy - 1);
                }
                else
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
            sum += (n - ni + 1) * (nj - yl + 1) * (yr - nj + 1);
        }
        vis[nj] = ni;
    }
    return sum;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n * m; i++)
        {
            C[i].clear();
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%lld", &w[i][j]);
                C[w[i][j]].push_back(make_pair(i, j));
            }
        }
        LL sum = 0;
        for (int i = 0; i <= n * m; i++)
        {
            if (!C[i].empty())
            {
                sort(C[i].begin(), C[i].end());
                sum += calc(i);
            }
        }
        LL num = n * (n + 1) * m * (m + 1) / 4;
        double ans = (sum * 1.0) / num;
        printf("%.9lf\n", ans);
    }
    return 0;
}