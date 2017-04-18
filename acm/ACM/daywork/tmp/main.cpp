#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;
char mymap[30][30];
char mymap1[30][30];
int a,b,c,d,e;
int M,N;
int mycont;
int flag;
int tmpcont=0;
void dfs(int qiy,int qix)
{

       // if(qiy==3&&qix==2)
                //cout<<mymap[qiy][qix]<<"  "<<endl;
    if(mymap[qiy][qix]=='X'||qiy<0||qiy>=M||qix<0||qix>=N||flag==1||mymap1[qiy][qix]=='X')
        {
            return;
        }
    if(mymap[qiy][qix]=='a')
    {
        a--;
        mymap[qiy][qix]='.';
    }

    if(mymap[qiy][qix]=='b')
    {
        b--;
        //cout<<b<<"这是ｂ"<<endl;
        mymap[qiy][qix]='.';
    }

    if(mymap[qiy][qix]=='c')
    {
        c--;
        mymap[qiy][qix]='.';
    }

    if(mymap[qiy][qix]=='d')
    {
        d--;
        mymap[qiy][qix]='.';

    }

    if(mymap[qiy][qix]=='e')
    {
        e--;
        mymap[qiy][qix]='.';
    }

    if(mymap[qiy][qix]=='A')
    {
        if(a==0)
        {
           mymap[qiy][qix]='.';
        }

        return;


    }
    if(mymap[qiy][qix]=='B')
    {
        if(b==0)
        {
             mymap[qiy][qix]='.';
            // cout<<"打开Ｂ"<<endl;

        }

        return;

    }
    if(mymap[qiy][qix]=='C')
    {
        if(c==0)
        mymap[qiy][qix]='.';
        return;

    }
    if(mymap[qiy][qix]=='D')
    {
        if(d==0)
        mymap[qiy][qix]='.';
        return;

    }
    if(mymap[qiy][qix]=='E')
    {
        if(e==0)
        mymap[qiy][qix]='.';
        return;
    }
    if(mymap[qiy][qix]=='G')
    {
        cout<<"YES"<<endl;
        flag=1;
        return;
    }
   mycont++;
    mymap1[qiy][qix]='X';

    dfs(qiy+1,qix);
    dfs(qiy-1,qix);
    dfs(qiy,qix+1);
    dfs(qiy,qix-1);

}
int main()
{
   // ifstream cin("1.txt");
    while(cin>>M>>N,M+N)
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
                   qix=j;
                   qiy=i;
               }

               mymap[i][j]=tmp;
            }
        }
        flag =0;

        while(true)
        {
            mycont=0;
            memset(mymap1,'0',sizeof(mymap1));
            dfs(qiy,qix);
            if(flag==1)
                break;
            //cout<<tmpcont<<"    "<<mycont<<endl;
            if(tmpcont==mycont)
            {
                cout<<"NO"<<endl;
                break;
            }
            tmpcont=mycont;

        }
        //cout<<mymap[2][2]<<endl;

    }
    return 0;
}
