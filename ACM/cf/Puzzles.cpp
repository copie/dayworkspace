#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int a[10000];
    for (int i = 0; i < m; i++)
        cin >> a[i];
    sort(a, a + m);
    int minx = 0x3f3f3f3f;
    for (int i = 0; i <= m - n; i++)
    {
        // cout << i << endl;
        minx = min(minx, a[i + n - 1] - a[i]);
    }
    cout << minx << endl;
    return 0;
}