#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

struct node{
int x;
int y;
int bu;
};
struct cmp1
{
    bool operator ()(struct node &a,struct node &b)
    {
        return a.bu>b.bu;//最小值优先
    }
};
int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

char mymap[310][310];
int m,n;
int xx=0;
int main()
{

    while(scanf("%d%d",&m,&n))
    {

        if(!(m+n))
            break;
        int x,y;
        int xend,yend;
        getchar();
        priority_queue<node,vector<node>,cmp1>que1;//最小值优先
        for(int i=0;i<m;i++)
        {
           for(int j=0;j<n;j++)
           {
            scanf("%c",&mymap[i][j]);
            if(mymap[i][j]=='Y')
            {
                y=i;
                x=j;
                mymap[i][j]='E';
            }
            if(mymap[i][j]=='T')
            {
                yend=i;
                xend=j;
                mymap[i][j]='E';
            }

           }
           getchar();
        }
        struct node tmp;
        tmp.y=y;
        tmp.x=x;
        tmp.bu=0;
        que1.push(tmp);
        mymap[y][x]='S';
        while(!que1.empty())
        {
            tmp=que1.top();
            que1.pop();
           // cout<<tmp.y<<"  tmp.y  "<<tmp.x<<"  df"<<endl;
            if(tmp.y==yend&&tmp.x==xend)
            {
                printf("%d\n",tmp.bu);
                xx=1;
                break;
            }
            for(int i=0;i<4;i++)
            {
                struct node tmp2;
                tmp2.y=tmp.y+dir[i][0];
                tmp2.x=tmp.x+dir[i][1];
                if(mymap[tmp2.y][tmp2.x]=='E')
                    tmp2.bu=tmp.bu+1;
                if(mymap[tmp2.y][tmp2.x]=='B')
                    tmp2.bu=tmp.bu+2;
                if(tmp2.x>=0&&tmp2.y>=0&&tmp2.x<n&&tmp2.y<m&&(mymap[tmp2.y][tmp2.x]=='E'||mymap[tmp2.y][tmp2.x]=='B'))
                {
                    mymap[tmp2.y][tmp2.x]='S';
                    que1.push(tmp2);
                }
            }
        }
        if(xx==0)
        {
            printf("-1\n");
        }
        xx=0;

    }
    return 0;
}
