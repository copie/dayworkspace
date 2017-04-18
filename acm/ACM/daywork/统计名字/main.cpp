#include <iostream>
#include <map>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    map<string,int> mm;
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;
        string tmp="000000000000000000000000000000";
        for(auto c:str)
        {
           tmp[int(c-'A')]=char(tmp[int(c-'A')]+1);
        }
        mm[tmp]++;
        cout<<mm[tmp]-1<<endl;
    }
    return 0;
}
