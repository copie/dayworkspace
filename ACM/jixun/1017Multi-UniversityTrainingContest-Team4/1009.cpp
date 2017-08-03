#include <bits/stdc++.h>

using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        cin>>n;
        int o=0;
        int ll =n;
        while(n--)
        {
            int tmp;
            scanf("%d",&tmp);
            if(tmp%2==0)
                o++;
        }
        if(o>=ll/2)
        cout<<"2"<<" "<<"0"<<endl;
        else
        cout<<2<<" "<<1<<endl;
    }
    return 0;
}