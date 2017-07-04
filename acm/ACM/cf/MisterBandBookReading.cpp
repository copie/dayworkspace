#include<iostream>

using namespace std;

int main()
{
    int c,v0,v1,a,l;
    int ans=1;
    int p=0;
    cin>>c>>v0>>v1>>a>>l;
    p=v0;

    while(p<c)
    {
        ans++;
        p-=l;

        if(v0+a*(ans-1)>v1)
        p+=v1;
        else
        p+=v0+a*(ans-1);
    }
    cout<<ans<<endl;

}