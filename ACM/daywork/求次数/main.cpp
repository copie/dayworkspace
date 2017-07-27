#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <string.h>
#include <sstream>

using namespace std;

int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        int n;
        char str[100020];
        cin>>n>>str;
        string str1{str};
        for(int i=0;i<strlen(str);i++)
        {
           string  s=str1.substr(i,i+n-1);
            cout<<s<<endl;
            char schar[100020];
            stringstream ss;
            ss<<s;
            ss>>schar;
            //cout<<schar<<endl;

        }

    }
    return 0;
}
