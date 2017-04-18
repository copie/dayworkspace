#include <iostream>
#include <bits/stdc++.h>

using namespace std;
struct Node
{
    int num;
    char ch1,ch2;
};
Node a[70];
int sum,i=0;
int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        int flag=1;
        int P,Q,a,b;
        map<int,stack<int> > MS;
        cin>>P>>Q;
        MS[1].push(70);
        for(int i=0; i<P; i++)
        {
            MS[1].push(P-i);//cout<<MS[1].top()<<endl;
        }
        MS[2].push(70);MS[3].push(70);
        for(int i=0; i<Q; i++)
        {
            cin>>a>>b;
            if(flag==0)continue;
            if(MS[a].top()==70||MS[a].top()>MS[b].top())
                flag=0;
            else
                {
                    MS[b].push(MS[a].top());
                    MS[a].pop();
                }
        }
        if(flag)
            cout<<"legal"<<endl;
        else
            cout<<"illegal"<<endl;
    }
    return 0;
}

