#include <stdio.h>
#include <string.h>
int P,Q;
int bian[1005];
bool map[1005][1005],vis[1005];
void dfs(int cur)
{
    vis[cur]=true;
    for(int i=1;i<=P;i++)
        if(map[cur][i])
        {
            bian[cur]++;
            if(!vis[i])
                dfs(i);
        }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int ok=1;
        memset(map,false,sizeof(map));
        memset(vis,false,sizeof(vis));
        memset(bian,0,sizeof(bian));

        scanf("%d%d",&P,&Q);

        for(int i=0;i<Q;i++)
        {
            int A,B;
            scanf("%d%d",&A,&B);
            map[A][B]=true,map[B][A]=true;
        }

        dfs(1);   // 判断是否连通的，如果vis有个false，就不是连通的

        for(int i=1;i<=P;i++)
            if(!vis[i])
            {
                ok=0;
                break;
            }

        if(!ok)printf("No\n");
        else
        {
            int xx=0;
            for(int i=1;i<=P;i++)
                if(bian[i]%2)xx++;
            if(xx==0||xx==2)printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
