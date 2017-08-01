#include <bits/stdc++.h>
#define MOD 1e9+7
using namespace std;
int main()
{
    long long  n,k;
    int i=0;
    while(cin>>n>>k)
    {
        long long sum=1;
        while(k)
        {
            
            if(k&1)
            {
                n %= (long long)(MOD);
                sum %= (long long)(MOD);
                sum *= n;
                sum%=(long long)(MOD);
            }
            n %= (long long)(MOD);
            n*=n;
            n %= (long long)(MOD);
            k=k>>1;
        }
        // cout<<sum<<endl;
        i++;
        printf("Case #%d: %lld\n",i,sum);
    }
    return 0;
}