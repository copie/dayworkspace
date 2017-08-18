#include <bits/stdc++.h>

using namespace std;
int dir[8][2]={1,1,1,0,1,-1,0,1,0,-1,-1,1,-1,0,-1,-1};
int mymap[1005][11005];
int a[16777220]={0};
int main()
{
    int M,N,TOL;
    cin>>N>>M>>TOL;
    stack<int> st;

    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            cin>>mymap[i][j];
            a[mymap[i][j]]++;
        }
    }
    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(a[mymap[i][j]]!=1)
            continue;
            bool x=true;
            for(int k=0;k<8;k++)
            {
                if(i+dir[k][0]>=1&&i+dir[k][0]<=M&&j+dir[k][1]>=1&&j+dir[k][1]<=N)
                        x = x && ((abs(mymap[i][j]-mymap[i+dir[k][0]][j+dir[k][1]]) > TOL ? true : false));
            }
            if(x==true)
            {
                if(!st.empty())
                {
                    cout<<"Not Unique"<<endl;
                    return 0;
                }
                else
                {
                    st.push(i);
                    st.push(j);
                }
            }
        }
    }
    if(!st.empty())
    {
        int tmp1;
        int tmp2;
        tmp1=st.top();
        st.pop();
        tmp2=st.top();
        st.pop();
        cout<<"("<<tmp1<<", "<<tmp2<<"): "<<mymap[tmp2][tmp1]<<endl;
    }
    else
    {
        cout<<"Not Exist"<<endl;
    }
}