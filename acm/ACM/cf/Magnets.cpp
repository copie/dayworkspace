#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int sum=0;
    int n;
    int a;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            cin>>a;
            sum++;        
        }
        else
        {
            int tmp;
            cin>>tmp;
            if(tmp!=a)
            {
                sum++;
                a=tmp;
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}