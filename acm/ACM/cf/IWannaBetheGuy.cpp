#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    set<int>se;
    int n;
    cin>>n;
    int m;
    cin>>m;
    while(m--)
    {
        int tmp;
        cin>>tmp;
        se.insert(tmp);
    }
    cin>>m;
    while(m--)
    {
        int tmp;
        cin>>tmp;
        se.insert(tmp);
    }
    if(se.size()==n)
    cout<<"I become the guy."<<endl;
    else
    cout<<"Oh, my keyboard!"<<endl;
    return 0;
}