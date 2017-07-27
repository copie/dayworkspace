#include <iostream>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int N;
        cin>>N;
        int a,sum[100010];
        int x=0;
        for(int i=1;i<=N;i++)
        {
            if(i==1)
            {
                cin>>a;
                sum[1]=a;
            }
            else
            {
                cin>>a;
                sum[i]=sum[i-1]+a;
            }
            if(i>=4)
            {
                if(sum[i]==sum[i-1]+sum[i-2]+sum[i-3])
                  x++;
            }

        }
        cout<<x<<endl;
    }
    return 0;
}
