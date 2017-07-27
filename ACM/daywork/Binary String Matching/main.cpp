#include <iostream>
#include <map>
#include <stdio.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        map<string,int> mymap;
        string a;
        string b;
        int sum=0;
        getchar();
        cin>>a>>b;
        if(a.length()>b.length())
        {
            cout<<0<<endl;
            continue;
        }
        for(int i=0;i<=b.length()-a.length();i++)
        {
            string tmp;
            for(int j=i;j<i+a.length();j++)
               tmp+=b[j];
            if(tmp==a)
                sum++;
        }
        cout<<sum<<endl;
    }
    return 0;
}
