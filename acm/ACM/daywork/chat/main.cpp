#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        long long n,m,x,y;

        struct ren{
        long long be;
        long long en;
        }a[200];
        cin>>n>>m>>x>>y;
        int f=0;
        for(int i=0;i<x;i++)
        {
            long long be,en;
            cin>>be>>en;
            if(be>=n)
                be=n;
            if(en>=n)
                en=n;
                a[f].be=be;
                a[f].en=en;
                f++;
        }
        long long  sum=0;
        for(int i=0;i<y;i++)
        {
            long long be,en;
            cin>>be>>en;
            int tmp1,tmp2;
            if(be>=n)
                be=n;
            if(en>=n)
                en=n;
                for(int j=0;j<f;j++)
                {
                    if(be>a[j].be&&en<a[j].en)
                    {
                        tmp1=be;
                        tmp2=en;
                    }
                    else if(be<a[j].be&&en>a[j].en)
                    {
                        tmp1=a[j].be;
                        tmp2=a[j].en;
                    }
                    else if(be<a[j].be&&en<a[j].en)
                    {
                        tmp1=a[j].be;
                        tmp2=en;
                    }
                    if((tmp2-tmp1)+1>=m)
                        sum+=(tmp2-tmp1-1);
                }

        }
        printf("%lld\n",sum);
    }
    return 0;
}
