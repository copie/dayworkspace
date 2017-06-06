#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define INF 0x3f
using namespace std;

struct node{
int y;
int quan;

}t;

vector<node>mymap[20];
queue<int>Q;
int d[20];
int xx[20];
int main()
{
    int n=7;
    int l=12;

    memset(d,INF,sizeof(d));
    memset(xx,INF,sizeof(xx));
    /*
1 2 24
1 3 8
1 4 15
2 5 6
3 5 7
3 6 3
4 7 4
5 7 9
6 7 3
6 4 5
7 2 3
6 5 2
    */
    for(int i=1;i<=l;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        t.quan=c;
        t.y=b;
        mymap[a].push_back(t);
    }
    Q.push(1);
    d[1]=0;
    xx[1]=0;
    while(!Q.empty())
    {
        int tmp=Q.front();
        Q.pop();
        xx[tmp]=INF;
        for(unsigned int i=0;i<mymap[tmp].size();i++)
        {
           if(mymap[tmp][i].quan+d[tmp]<d[mymap[tmp][i].y]) //
           {
               d[mymap[tmp][i].y]=mymap[tmp][i].quan+d[tmp];
               if(xx[mymap[tmp][i].y]!=0)
               {
                  Q.push(mymap[tmp][i].y);
                  xx[mymap[tmp][i].y]=0;
               }
           }

        }
        for(int i=1;i<n+1;i++)
        cout<<d[i]<<"  ";
        cout<<endl;
    }
    for(int i=1;i<n+1;i++)
        cout<<d[i]<<"  ";
    cout<<endl;
    return 0;
}

