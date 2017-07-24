// #include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

char mymap[100][100];
int n, k;
int visx[100];
int visy[100];
int ans;
void dfs(int i, int sum)
{
    if (i > n)
        return;
    if (sum == k)
    {
        ans++;
        return;
    }
    for (int j = 0; j < n; j++)
    {
        if (mymap[i][j] == '#' && visx[i] == 0 && visy[j] == 0)
        {

            visx[i] = 1;
            visy[j] = 1;
            dfs(i + 1, sum + 1);
            visx[i] = 0;
            visy[j] = 0;
        }
    }
    dfs(i + 1, sum);
}
int main()
{
    while (scanf("%d%d", &n, &k), n != -1 && k != -1)
    {
        ans = 0;
        memset(visx, 0, sizeof(visx));
        memset(visy, 0, sizeof(visy));
        for (int i = 0; i < n; i++)
        {
            scanf("%s", mymap[i]);
        }
        dfs(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}