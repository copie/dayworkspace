#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n,k;
    int c=1;
    while(cin>>n>>k)
    {
        printf("Case #%d: ",c++);
        if(k<=n)
        {
            cout<<k<<endl;
        }
        else
        {
            if((k-n)/(n-1)==0)
            {
                if((k-n)%(n-1)==0)
                cout<<n-1<<endl;
                else
                cout<<(k-n)%(n-1)<<endl;
            }
            else
            {
                 if((k-n)%(n-1)==0)
                 cout<<n<<endl;
                 else
                 cout<<(k-n)%(n-1)<<endl;
            }
        }
    }
    return 0;
}