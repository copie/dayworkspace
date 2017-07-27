#include <iostream>
#include <queue>

using namespace std;

int main()
{

    int T;
    cin>>T;
    while(T--)
    {

        int n;
        cin>>n;
        if(n==0)
        {
            cout<<0<<endl;
            continue;
        }
        int sum=1;
        int a[100010]={0};
        int x=0;
        for(int i=0;i<n;i++)
        {
            int tmp;
            cin>>tmp;
            a[i]=tmp;
            if(i>0&&tmp-a[i-1]==1)
            {
                x++;

                if(x==4)
                {
                    sum++;
                    x=0;
                }
            }
            else if(tmp-a[i-1]>1)
            {
                 sum=max(1,sum-tmp-a[i-1]);
                 //cout<<sum<<"sum"<<endl;
                 x=0;
            }
            else
            {
                x=0;
            }
        }

        cout<<sum+a[n-1]+5<<endl;


    }
    return 0;
}
