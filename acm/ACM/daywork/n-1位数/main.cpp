#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
       string str;
       cin>>str;
       str=str.substr(1);
       stringstream ss;
       ss<<str;
       int a;
       ss>>a;
       cout<<a<<endl;
    }


    return 0;
}
