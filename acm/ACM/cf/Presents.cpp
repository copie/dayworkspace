#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    map<int,int> mymap;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int tmp;
        cin>>tmp;
        mymap[tmp]=i;
    }
    cout<<mymap[1];
    for(int i=2;i<=n;i++)
    cout<<" "<<mymap[i];
    cout<<endl;
    return 0;
}