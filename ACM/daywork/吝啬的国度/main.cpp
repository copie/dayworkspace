#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
vector<int> mymap[100001];
int p[100001];
void dfs(int g)
{

    for(auto jie : mymap[g])
    {
        if(p[jie]!=0)
        continue;
        p[jie]=g;
        dfs(jie);
    }
   /* for(int i=0;i<mymap[g].size();i++)
    {
        if(p[mymap[g][i]]!=0)
        continue;
        p[mymap[g][i]]=g;
        dfs(mymap[g][i]);
    }*/
}

int main()
{
    int M;
    cin>>M;
    while(M--)
    {
        memset(mymap,0,sizeof(mymap));
        memset(p,0,sizeof(p));
        int N,S;
        cin>>N>>S;
        p[S]=-1;
        for(int i=0;i<N-1;i++)
        {
            int q,h;
            cin>>q>>h;
            mymap[q].push_back(h);
            mymap[h].push_back(q);
        }
        dfs(S);
        cout<<p[1];
        for(int i=2;i<=N;i++)
            cout<<" "<<p[i];
        cout<<endl;
    }

    return 0;
}
