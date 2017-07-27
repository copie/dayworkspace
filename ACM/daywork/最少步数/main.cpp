#include <iostream>
#include <queue>

using namespace std;
struct node{
int x;
int y;
int bu;
};
int a,b,c,d;
queue<node> Q;
int map[9][9]={
 {1,1,1,1,1,1,1,1,1},
 {1,0,0,1,0,0,1,0,1},
 {1,0,0,1,1,0,0,0,1},
 {1,0,1,0,1,1,0,1,1},
 {1,0,0,0,0,1,0,0,1},
 {1,1,0,1,0,1,0,0,1},
 {1,1,0,1,0,1,0,0,1},
 {1,1,0,1,0,0,0,0,1},
 {1,1,1,1,1,1,1,1,1}
};
int mymap[9][9]={
 {1,1,1,1,1,1,1,1,1},
 {1,0,0,1,0,0,1,0,1},
 {1,0,0,1,1,0,0,0,1},
 {1,0,1,0,1,1,0,1,1},
 {1,0,0,0,0,1,0,0,1},
 {1,1,0,1,0,1,0,0,1},
 {1,1,0,1,0,1,0,0,1},
 {1,1,0,1,0,0,0,0,1},
 {1,1,1,1,1,1,1,1,1}
};
int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
void bfs(int x,int y,int bu)
{
    struct node tmp1;
    struct node tmp2;
    tmp1.x=x;
    tmp1.y=y;
    tmp1.bu=bu;
    Q.push(tmp1);
    while(!Q.empty())
    {
        tmp1=Q.front();
        map[tmp1.x][tmp1.y]=1;
        Q.pop();
       //cout<<tmp1.x<<" "<<tmp1.y<<" "<<tmp1.bu<<endl;
        //cout<<(tmp1.x==c&&tmp1.y==d)<<endl;
        //cout<<c<<" "<<d<<endl;
        if(tmp1.x==c&&tmp1.y==d)
        {
            cout<<tmp1.bu<<endl;
            return ;
        }

        for(int i=0;i<4;i++)
        {
            tmp2.x=tmp1.x+dir[i][0];
            tmp2.y=tmp1.y+dir[i][1];
            tmp2.bu=tmp1.bu+1;

            if(tmp2.x>0&&tmp2.y>0&&tmp2.x<9&&tmp2.y<9&&map[tmp2.x][tmp2.y]==0)
            Q.push(tmp2);
        }

    }


}
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        //int a,b,c,d;
         while(!Q.empty())
            Q.pop();
         for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            map[i][j]=mymap[i][j];
        cin>>a>>b>>c>>d;
        bfs(a,b,0);

    }
    return 0;
}
