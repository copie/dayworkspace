/*#include <iostream>
#include <string.h>
#include <stdio.h>

#define INF 0x3f3f3f3f
using namespace std;
int mymap[110][110];
int cha=INF;
int N;
int dir[4][2]={0,-1,0,1,-1,0,1,0};
int visit[110][110];
void dfs(int da,int xiao,int y,int x)
{
    if(y==N-1&&x==N-1)
    {
        cha=min(cha,da-xiao);
        return;
    }
    int tmpda,tmpxiao;
    for(int i=0;i<4;i++)
    {
        int tmpy=y+dir[i][0];
        int tmpx=x+dir[i][1];
        if(tmpx>=0&&tmpx<N&&tmpy>=0&&tmpx<N&&visit[tmpy][tmpx]==0)
        {
            visit[tmpy][tmpx]=1;
        if(mymap[tmpy][tmpx]>da)
        {
            tmpda=mymap[tmpy][tmpx];

            if(tmpda-xiao>cha)
                continue;
            dfs(tmpda,xiao,tmpy,tmpx);
                 //visit[tmpy][tmpx]=0;
        }
        else if(mymap[tmpy][tmpx]<xiao)
        {
            tmpxiao=mymap[tmpy][tmpx];
            if(da-tmpxiao>cha)
                continue;
            dfs(da,tmpxiao,tmpy,tmpx);
               // visit[tmpy][tmpx]=0;
        }
        else
        {
            if(da-xiao>cha)
                continue;
            dfs(da,xiao,tmpy,tmpx);
                //visit[tmpy][tmpx]=0;
        }
         visit[tmpy][tmpx]=0;
        }

    }

}

int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        cha=INF;
        memset(mymap,INF,sizeof(mymap));
        memset(visit,0,sizeof(visit));
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
                scanf("%d",&mymap[i][j]);
        }
        visit[0][0]=1;
        dfs(mymap[0][0],mymap[0][0],0,0);
        printf("%d",cha);
    }
    return 0;
}
*/
#include <iostream>
#include <string.h>

using namespace std;
int main()
{
    long long d[21],c[25][25];
    memset(c,0,sizeof(c));
    d[0]=1;
    d[1]=0;
    d[2]=1;
    for(int i=3;i<21;i++)
        d[i]=(i-1)*(d[i-1]+d[i-2]);

       c[0][0]=1;c[1][0]=1;c[1][1]=1;
    for(int i=2;i<21;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)
            c[i][j]=c[i-1][j]+c[i-1][j-1];
    }


    int N;
    cin>>N;
    while(N--)
    {
        int x,y;
        cin>>x>>y;

        cout<<c[x][y]*d[y]<<endl;
    }
}
