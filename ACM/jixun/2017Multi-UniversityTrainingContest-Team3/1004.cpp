#include <bits/stdc++.h>

using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int a[1000000];
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                for(int k = j+1;k<=n;k++)
                {
                    if((a[i]^a[j])<(a[j]^a[k]))
                    {
                        
                        sum++;
                    }
                }
            }
        }
        printf("%d\n",sum);       
    }
    return 0;
}