#include<iostream>
#include<cstring>
#include<cstdio>
#define T 1000050
#define inf 0x3f3f3f3f

using namespace std;

int a[T],box[T];
int Find(int x)
{
    if(x==box[x])
        return x;
    else
        return Find(box[x]);
}
int main()
{
    int n,m;
    int j=0;
    int k;
    while(cin>>n>>m)
    {
        k=n;
        for(int i=0;i<n;++i)
        {
            a[i]=box[i]=i;
        }
        while(m--)
        {
            char ch;
            cin>>ch;
            if(ch=='U')
            {
                int tmp1,tmp2;
                cin>>tmp1>>tmp2;
                int x=Find(a[tmp1]);
                int y=Find(a[tmp2]);
                if(x!=y)
                {
                    box[x]=y;
                }
            }
            else
            {
               int tmp;
               cin>>tmp;
               box[k]=k;
               a[tmp]=k++;
            }
        }
       int bo[T]={0};
       for(int i=0,k=0;i<n;++i)
       {
           if(!bo[Find(a[i])])bo[Find(a[i])]=1,k++;
       }
       printf("Case #%d: %d\n",++j,k);

    }
}
