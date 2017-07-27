#include <iostream>
#include <string.h>

#define INF 0x3f3f3f3f
using namespace std;

int shib[105];
int chens[1005][1005];
int dist[1005];
int N,M,P,Q;

bool pan(int a)
{
    for(int i=0;i<N;i++)
    {
        if(shib[i]==a)
            return true;
    }
    return false;
}
void Dijkstra()
{
    int s[10005];
    int mindis,u;
    for(int i=0;i<M;i++)
    {
        dist[i]=chens[Q][i];
        s[i]=0;
    }
    s[Q]=1;
    for(int i=0;i<M;i++)
    {
        mindis = INF;
        for(int j=0;j<M;j++)
        {
            if(s[j]==0&&dist[j]<mindis)
            {
                u=j;
                mindis = dist[j];
            }
        }
        s[u]=1;
        for(int j=0;j<M;j++)
        {
            if(s[j]==0)
            {
                if(chens[u][j]<INF&&dist[u]+chens[u][j]<dist[j])
                {
                    dist[j]=dist[u]+chens[u][j];
                }
            }
        }
    }
}
int main()
{
   int T;
   cin>>T;
   while(T--)
   {
       memset(chens,0x3f3f3f3f,sizeof(chens));
       memset(shib,-1,sizeof(shib));
       cin>>N>>M>>P>>Q;
       for(int i=0;i<N;i++)
       {
           cin>>shib[i];
       }
       for(int i=0;i<P;i++)
       {
           int a,b,t;
           cin>>a>>b>>t;

           chens[a][b]=min(t,chens[a][b]);
           chens[b][a]=min(t,chens[b][a]);
       }
       if(pan(Q))
        cout<<0<<endl;
       else
       {
           Dijkstra();
       }
       int mm=INF;
       for(int i=0;i<M;i++)
        if(pan(i))
        {
            mm=min(mm,dist[i]);
        }
        cout<<mm<<endl;
   }
    return 0;
}
