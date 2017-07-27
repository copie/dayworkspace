    #include <bits/stdc++.h>

    #define INF 0x3f3f3f3f

    using namespace std;

    const int maxn = 110;
    int n, m; //n 景区的个数
    int Map[maxn][maxn];
    int dis[maxn];
    int vis[maxn];

    void init_map()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    Map[i][j] = 0;
                else
                    Map[i][j] = INF;
            }
    }
    void dijkstra(int start)
    {
        for (int i = 1; i <= n; i++)
        {
            dis[i] = Map[start][i];
            vis[i] = 0;
        }
        vis[start] = 1;
        int mindis, u;
        for (int i = 1; i <= n; i++)
        {
            mindis = INF;
            u = 0;
            /**每次让u = 0,不会与其他定点编号冲突，而且下个  
            for循环执行完后，u还等于0，则程序就可以结束的，  
            在杭电写题得加上，不然的会显示RE，遇到过两次这样  
            的问题**/
            for (int j = 1; j <= n; j++)
            {
                if (vis[j] == 0 && dis[j] < mindis)
                {
                    mindis = dis[j];
                    u = j;
                }
            }
            if (u == 0)
                break;
            vis[u] = 1;
            for (int j = 1; j <= n; j++)
            {
                if (vis[j] == 0)
                {
                    if (Map[u][j] < INF && dis[u] + Map[u][j] < dis[j])
                        dis[j] = dis[u] + Map[u][j];
                }
            }
        }
    }

    int main()
    {
        // std::ios::sync_with_stdio(false);
        // cin.tie(0);
        while (~scanf("%d%d",&n,&m))
        {
            init_map();
            int a, b, c;
            for (int i = 0; i < m; i++)
            {
                // cin >> a >> b >> c;
                scanf("%d%d%d",&a,&b,&c);
                if (c < Map[a][b])
                {
                    Map[a][b] = Map[b][a] = c;
                }
            }
            int ans = INF;
            for (int i = 1; i <= n; i++)
            {
                for (int j = i+1; j <= n; j++)
                {
                    if(Map[i][j]!=INF)
                    {
                        int tmp = Map[i][j];
                        Map[i][j] = Map[j][i] = INF;
                        dijkstra(i);
                        ans = min(ans,dis[j]+tmp);
                        Map[i][j] = Map[j][i] = tmp;
                    }

                }
            }
            if(ans>=INF)
            {
                // cout<<"It's impossible."<<endl;
                printf("It's impossible.\n");
            }
            else
            {
                printf("%d\n",ans);
                // cout<<ans<<endl;
            }
        }
        return 0;
    }