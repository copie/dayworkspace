#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <stdio.h>

#define INF 0x3f3f3f3f
using namespace std;

struct node{
int y;
double quan;

}t;


double d[50005];
int xx[50005];
int main()
{
    int n;
    int l;
    int T;
    scanf("%d",&T);
    while(T--)
    {
    vector<node>mymap[10005];//vector 要初始化
    queue<int>Q;
    scanf("%d%d",&n,&l);
    memset(d,0xc0c0c0c0,sizeof(d));
    memset(xx,INF,sizeof(xx));

    for(int i=1;i<=l;i++)
    {
        int a,b;
        double c;
        cin>>a>>b>>c;
        t.quan=c/100.0;
        t.y=b;
        mymap[a].push_back(t);
        t.y=a;
        mymap[b].push_back(t);
    }
    Q.push(1);
    d[1]=1.0;
    xx[1]=0;
    while(!Q.empty())
    {
        int tmp=Q.front();
        Q.pop();
        xx[tmp]=INF;
        for(unsigned int i=0;i<mymap[tmp].size();i++)
        {
        if(mymap[tmp][i].quan*d[tmp]>d[mymap[tmp][i].y]) //
        {
            d[mymap[tmp][i].y]=mymap[tmp][i].quan*d[tmp];
            if(xx[mymap[tmp][i].y]!=0)
            {
                Q.push(mymap[tmp][i].y);
                xx[mymap[tmp][i].y]=0;
            }
        }

        }
    }

   printf("%.6lf\n",d[n]*100);
    }
    return 0;
}
