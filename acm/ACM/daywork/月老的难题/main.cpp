/*#include<iostream>
#include<cstring>
using namespace std;
int map[505][505];
int visit[505],flag[505];
int n,m;
bool dfs(int a)
{
    for(int i=1; i<=n; i++)
    {
        if(map[a][i]&&!visit[i])
        {
            visit[i]=1;
            if(flag[i]==0||dfs(flag[i]))
            {
                flag[i]=a;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int T;
    cin>>T;
    while(T--)

    {
        cin>>n>>m;
        memset(map,0,sizeof(map));
        for(int i=1; i<=m; i++)
        {
            int x,y;
            cin>>x>>y;
            map[x][y]=1;
        }
        memset(flag,0,sizeof(flag));
        int result=0;
        for(int i=1; i<=n; i++)
        {
            memset(visit,0,sizeof(visit));
            if(dfs(i))result++;
        }
        cout<<result<<endl;
    }
    return 0;
}
*/
#include<bits/stdc++.h>
using namespace std;
int n,m;
int vis[505];    //vis[i]记录某男配对时是否已考虑女孩i
int flag[505];    //flag[i]记录女孩i的当前男孩
vector<int> e[505];
bool dfs(int x)
{
    for(int i=0; i<e[x].size(); i++)
    {
        int g=e[x][i];
        if(!vis[g])
        {
            vis[g]=1;
            if(flag[g]==0||dfs(flag[g]))    //该女孩还没男票或这个女孩原来的男票可以另外去找别的女孩
            {
                flag[g]=x;        //男孩x与女孩g确立恋爱关系
                return true;    //男孩x成功找到女孩
            }
        }
    }
    return false;    //男孩x没有找到女票 T_T
}

int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++) e[i].clear();//令所有男孩没有可选择对象
        memset(flag,0,sizeof(flag));    //0即无，令所有女孩为单身
        while(m--)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            e[x].push_back(y);    //给男孩x增加一个可选择女孩y
        }
        int num=0;    //初始化成功配对数
        for(int i=1; i<=n; i++)        //从第一个男孩起开始解决相亲问题
        {
            memset(vis,0,sizeof(vis));
            if(dfs(i)) num++;    //男孩i成功找到女朋友，成功配对数++
        }
        printf("%d\n",num);
    }
}


