#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    stack<int>st;
    int x=0;
    int ans=0;
    for(int i = 0;i < 2 * n; i ++)
    {
        string str;
        cin>>str;
        if(str[0]=='a')
        {
            int a;
            cin>>a;
            st.push(a);
        }
        else
        {
            if(!st.empty())
            {
                if(st.top()==x+1)
                {
                   
                    st.pop();
                }
                else
                {
                    while(!st.empty())
                    {
                        st.pop();
                    }
                    ans++;
                }
            }
            x++;
        }
        
    }
    cout<<ans<<endl;
    return 0;
}