#include <bits/stdc++.h>

using namespace std;
struct node
{
    int n;
    int w;
};

vector<node> vag[600010];
int begin;
long long ans;

vector<int> onev1;
vector<int> onev2;
vector<int> onew;

long long dfs(long long sum, int dian, int shang)
{
    if (dian == begin)
    {
        for (auto x : onew)
        {
            sum *= x;
        }
        ans += sum;
        return 0;
    }
    for (auto x : vag[dian])
    {
        if (onev1.count(x.n) == 0 && onev2.count(x.n) == 0 && x.n != shang)
        {
            dfs(sum * x.w, x.n, dian);
        }
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ans = 0;
        int n;
        cin >> n;
        struct node tmp;
        for (int i = 1; i <= n; i++)
        {
            int v1, w1, v2, w2;
            cin >> v1 >> w1 >> v2 >> w2;
            v1 += n;
            v2 += n;
            tmp.n = v1;
            tmp.w = w1;
            vag[i].push_back(tmp);
            tmp.n = i;
            vag[v1 + n].push_back(tmp);
            tmp.n = v2;
            tmp.w = w2;
            vag[i].push_back(tmp);
            tmp.n = i;
            vag[v2 + n].push_back(tmp);
        }
        int flag = 0;
        for (int i = 2 * n; i > n; i--)
        {

            if (vag[i].size() == 1)
            {
                onev2.push_back(i);
                onev1.push_back(vag[i][0].n);
                onew.push_back(vag[i][0].w);
            }
            else
            {
                if (!flag)
                {
                    begin = i;
                }
            }
        }
        for (auto x : vag[begin])
        {
            if (onev1.count(x.n) == 0 && onev2.count(x.n) == 0)
                dfs(x.w, x.n, begin);
        }
    }
    return 0;
}