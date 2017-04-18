#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;
int dogbeginx,dogbeginy;
int doorx,doory;
int wall;
char mymap[200][200];
int flag;
int M,N,T;
int to[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};

void DFS(int x,int y,int cnt)
{
    if(x>M||y>N||x<=0||y<=0)
        return;
    if(cnt==T&&x==doorx&&y==doory)
        flag=1;
    if(flag)
        return;
    int s1 = x-doorx;
    int s2 = y-doory;
    if(s1<0)
    s1=-s1;
    if(s2<0)
    s2=-s2;
    int tem = T-cnt - s1 - s2;
    if(tem<0 || tem&1)
    return;
    for(int i=0;i<4;i++)
    {
        if(mymap[x+to[i][0]][y+to[i][1]]!='X')
        {
            mymap[x+to[i][0]][y+to[i][1]]='X';
            DFS(x+to[i][0],y+to[i][1],cnt+1);
            mymap[x+to[i][0]][y+to[i][1]]='.';
        }
    }
    return;
}
int main()
{

    while(cin>>M>>N>>T,M,N,T)
    {
        wall=0;
        memset(mymap,'X',sizeof(mymap));
        for(int i=1;i<=M;i++)
        {
            for(int j=1;j<=N;j++)
            {
                char tmp;
                cin>>tmp;
                if(tmp=='S')
                {
                    dogbeginx=i;
                    dogbeginy=j;
                }
                if(tmp=='D')
                {
                    doorx=i;
                    doory=j;
                }
                if(tmp=='X')
                {
                    wall++;
                }
                mymap[i][j]=tmp;
            }
        }
        if(N*M-wall<=T)
        {
            cout<<"NO"<<endl;
            continue;
        }
        flag=0;
         mymap[dogbeginx][dogbeginy]='X';
         DFS(dogbeginx,dogbeginy,0);
         if(flag)
            cout<<"YES"<<endl;
         else
            cout<<"NO"<<endl;

    }
    return 0;
}
