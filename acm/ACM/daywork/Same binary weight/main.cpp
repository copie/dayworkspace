#include <iostream>

using namespace std;

int main()
{
    int x;
    while(cin>>x)
    {
    int b=x&(-x);
    int t=x+b;
    int s=t^x;
    int k=(s>>2)/b;
    cout<<(t|k)<<endl;
    }
    return 0;
}
