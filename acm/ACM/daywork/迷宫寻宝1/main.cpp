#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
char mymap[30][30];
char mymap1[30][30];
int a,b,c,d,e;
int M,N;
int mycont;
int flag;
void dfs(int qix,int qiy)
{
    if(mymap[qix][qiy]=='X'||qix<0||qix>=M||qiy<0||qiy>=N||flag==1||mymap[qix][qiy]=='X')
        return;
    if(mymap[qix][qiy]=='a')
    {
        a--;
        mymap[qix][qiy]='.';
    }

    if(mymap[qix][qiy]=='b')
    {
        b--;
        mymap[qix][qiy]='.';
    }

    if(mymap[qix][qiy]=='c')
    {
        c--;
        mymap[qix][qiy]='.';
    }

    if(mymap[qix][qiy]=='d')
    {
        d--;
        mymap[qix][qiy]='.';

    }

    if(mymap[qix][qiy]=='e')
    {
        e--;
        mymap[qix][qiy]='.';
    }

    if(mymap[qix][qiy]=='A')
    {
        if(a==0)
        mymap[qix][qiy]='.';

    }
    if(mymap[qix][qiy]=='B')
    {
        if(b==0)
        mymap[qix][qiy]='.';

    }
    if(mymap[qix][qiy]=='C')
    {
        if(c==0)
        mymap[qix][qiy]='.';

    }
    if(mymap[qix][qiy]=='D')
    {
        if(d==0)
        mymap[qix][qiy]='.';

    }
    if(mymap[qix][qiy]=='E')
    {
        if(e==0)
        mymap[qix][qiy]='.';
    }
    if(mymap[qix][qiy]=='G')
    {
        cout<<"Yes"<<endl;
        flag=1;
        return;
    }
    mycont++;
    mymap1[qix][qiy]='X';
    dfs(qix+1,qiy);
    dfs(qix-1,qiy);
    dfs(qix,qiy+1);
    dfs(qix,qiy-1);

}
int main()
{

    while(cin>>M>>N||M||N)
    {   a=b=c=d=0;
        int qix,qiy;
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<N;j++)
            {
               char tmp;
               cin>>tmp;
               if(tmp=='a')
               a++;
               if(tmp=='b')
               b++;
               if(tmp=='c')
               c++;
               if(tmp=='d')
               d++;
               if(tmp=='e')
               e++;
               if(tmp=='S')
               {
                   qix=i;
                   qiy=j;
               }

               mymap[i][j]=tmp;
            }
            getchar();
        }
        flag =0;
        int tmpcont=0;
        while(true)
        {
            mycont=0;
            memset(mymap1,'0',sizeof(mymap1));
            dfs(qix,qiy);
            if(flag==1)
                break;
            if(tmpcont==mycont)
            {
                cout<<"No"<<endl;
            }
            tmpcont=mycont;

        }
    }
    return 0;
}
