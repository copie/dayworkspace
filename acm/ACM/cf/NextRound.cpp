#include<iostream>

using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    int a[100];
    for(int i=0;i<n;i++)
        cin>>a[i];
    int sum=0;
    if(a[k-1]==0)
    {
        for(int i=0;i<n;i++)
            if(a[i]>a[k-1])
                sum++;
    }
    else
    {
        for(int i=0;i<n;i++)
            if(a[i]>=a[k-1])
                sum++;
    }
    cout<<sum<<endl;
}