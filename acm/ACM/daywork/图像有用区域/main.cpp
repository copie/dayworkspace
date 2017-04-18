#include <iostream>
#include <queue>

using namespace std;
int mymap[969][1449];

struct node {
int y;
int x;
};
queue<node> Q;
int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int w,h;
void bfs(int y,int x)
{
    struct node tmp1,tmp2;
    tmp1.y=y;
    tmp1.x=x;
    Q.push(tmp1);
    while(!Q.empty())
       {
        tmp1=Q.front();
        mymap[tmp1.y][tmp1.x]=0;
        Q.pop();

        for(int i=0;i<4;i++)
        {
            tmp2.y=tmp1.y+dir[i][0];
            tmp2.x=tmp1.x+dir[i][1];


            if(tmp2.x>=0&&tmp2.y>=0&&tmp2.x<=w+1&&tmp2.y<=h+1&&mymap[tmp2.y][tmp2.x]!=0)
            {
                Q.push(tmp2);

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

        cin>>w>>h;
        for(int i=0;i<=h+1;i++)
        {
            for(int j=0;j<=w+1;j++)
            {
                if(i==0||j==0||i==h+1||j==w+1)
                    mymap[i][j]=255;
                else
                    cin>>mymap[i][j];
            }
        }
        bfs(0,0);
        for(int i=1;i<=h;i++)
        {
            for(int j=1;j<=w;j++)
            {

                    cout<<mymap[i][j]<<" ";
            }
            cout<<endl;
        }

    }
    return 0;
}
