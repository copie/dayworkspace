#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin>>n;
    int sum1=0,sum2=0,sum3=0;
    for(int i=0;i<n;i++)
    {
        int tmp1,tmp2,tmp3;
        cin>>tmp1>>tmp2>>tmp3;
        sum1+=tmp1;
        sum2+=tmp2;
        sum3+=tmp3;
    }
    if(sum1==0&&sum2==0&&sum3==0)

    
    cout<<"YES"<<endl;
    else
    cout<<"NO"<<endl;
    
    return 0;
}