#include <bits/stdc++.h>

using namespace std;
struct node
{
    int n;
    int w;
};

vector<node> vag[600010];
int mybegin;
long long ans;

vector<int> onev1;
vector<int> onev2;
vector<int> onew;

long long dfs(long long sumj, int dian, int shang, bool jo, long long sumo)
{

    jo = !jo;
    if (dian == mybegin)
    {
        for (auto x : onew)
        {
            sumj *= x;
            sumo *= x;
        }
        ans += sumj + sumo;
        return 0;
    }
    for (auto x : vag[dian])
    {
        if (count(onev1.begin(), onev1.end(), x.n) == 0 && count(onev2.begin(), onev2.end(), x.n) == 0 && x.n != shang)
        {
            if (jo)
                dfs(sumj * x.w, x.n, dian, jo, sumo);
            else
                dfs(sumj, x.n, dian, jo, sumo * x.w);
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
            vag[v1].push_back(tmp);
            tmp.n = v2;
            tmp.w = w2;
            vag[i].push_back(tmp);
            tmp.n = i;
            vag[v2].push_back(tmp);
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
                    mybegin = i;
                }
            }
        }
        for (auto x : vag[mybegin])
        {

            if (count(onev1.begin(), onev1.end(), x.n) == 0 && count(onev2.begin(), onev2.end(), x.n) == 0)
            {
                dfs(x.w, x.n, mybegin, 1, 1);
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
