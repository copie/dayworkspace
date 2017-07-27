#include <bits/stdc++.h>
#define MIN(x, y) (x < y ? x : y)
using namespace std;
const int INF = 0x3f3f3f;
const int MAXN = 110;
int Map[MAXN][MAXN], dis[MAXN][MAXN], anser;
int N, M;
void initial()
{
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= 100; j++)
            if (i - j)
                Map[i][j] = INF;
            else
                Map[i][j] = 0;
}
void floyd()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            dis[i][j] = Map[i][j];
    anser = INF;
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (i != j && i != k && j != k)
                    anser = MIN(anser, dis[i][j] + Map[j][k] + Map[k][i]);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                dis[i][j] = MIN(dis[i][j], dis[i][k] + dis[k][j]);
    }
    if (anser == INF)
        cout << "It's impossible." << endl;
    else
        printf("%d\n", anser);
}
int main()
{
    int a, b, c;
    while (~scanf("%d%d", &N, &M))
    {
        initial();
        while (M--)
        {
            scanf("%d%d%d", &a, &b, &c);
            if (c < Map[a][b])
                Map[a][b] = Map[b][a] = c;
        }
        floyd();
    }
    return 0;
}