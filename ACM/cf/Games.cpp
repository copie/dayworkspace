#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin>>n;
    int a[10000],b[10000];
    for(int i=0;i<n;i++)
    cin>>a[i]>>b[i];
    int sum=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j&&a[i]==b[j])
            sum++;
        }
    }   
    cout<<sum<<endl;
    return 0;
}