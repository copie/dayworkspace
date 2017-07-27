#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int m;
    while (cin >> m)
    {
        map<string, int> mymap;
        int wen = 0;
        int  flag=-1;
        for(int i=1;i<=m;i++)
        {
            char c;
            string str;
            cin >> c;
            if (c == '?')
            wen++;
            if(c=='I')
            {
                cin>>str;
                mymap[str]=1;
            }
            if(c=='O')
            {
                cin>>str;
                if(mymap[str]==1)
                mymap[str]=0;
                else
                {
                    if(wen>0)
                    wen--;
                    else
                    {
                        if(flag==-1)
                        flag=i;
                    }
                }
            }
        }
        cout<<flag<<endl;
    }

    return 0;
}