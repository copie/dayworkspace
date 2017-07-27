#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        double a,b,c;
        cin>>a>>b>>c;
        cout<<"Case #"<<i+1<<": ";


        if(a+b<=c)
        cout<<"false"<<endl;
        else
        cout<<"true"<<endl;
    }
}