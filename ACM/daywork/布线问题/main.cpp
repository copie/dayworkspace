#include <iostream>
#include <string.h>

#define INF 0x3f3f3f3f
#define MAXV  505
using namespace std;
int n,e;
int mymap[MAXV][MAXV];
int sum=0;
void Prim(int v)
{
    int lowcost[MAXV];
    int min;
    int closest[MAXV],k;
    for(int i=1;i<=n;i++)
    {
        lowcost[i]=mymap[v][i];
        closest[i]=v;
    }
    for(int i=2;i<=n;i++)
    {
        min=INF;
        for(int j=1;j<=n;j++)
        {
            if(lowcost[j]!=0&& lowcost[j]<min)
            {
                min=lowcost[j];
                k=j;
            }
        }
        sum+=min;
        lowcost[k]=0;
       // cout<<closest[k]<<"  "<<k<<"   "<<min<<endl;
        for(int j=1;j<=n;j++)
        {
            if(mymap[k][j]!=0&&mymap[k][j]<lowcost[j])
            {
                lowcost[j]=mymap[k][j];
                closest[j]=k;
            }
        }
    }
}
int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        memset(mymap,INF,sizeof(mymap));
        cin>>n>>e;
        for(int i=1;i<=n;i++)
            mymap[i][i]=0;
        for(int i=1;i<=e;i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            mymap[a][b]=c;
            mymap[b][a]=c;
        }
        int minf=INF;
        int lou;
        for(int i=1;i<=n;i++)
        {
            int tmp;
            cin>>tmp;
            if(tmp<minf)
            {
                lou=i;
                minf=tmp;
            }
        }
    Prim(lou);
    cout<<sum+minf<<endl;
    sum=0;
    }
    return 0;
}
