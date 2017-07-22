#include <iostream>

using namespace std;

int main()
{
    int T;cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        int ans = (n/2)*(n-(n/2));
        cout<<ans<<endl;
    }
    return 0;
}