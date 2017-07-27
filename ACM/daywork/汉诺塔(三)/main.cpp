#include <iostream>
#include<stack>

using namespace std;

int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        stack<int> stk[4];
        int m,n;
        cin>>m>>n;

        stk[1].push(0x3f3f);
        for(int i=m;i>=1;i--)
        stk[1].push(i);
        stk[2].push(0x3f3f);
        stk[3].push(0x3f3f);
        int x=0;
        for(int i=0;i<n;i++)
        {

            int tmp1,tmp2;
            cin>>tmp1>>tmp2;
            if(x==1)
                continue;
            if(stk[tmp1].top()==0x3f3f)
            {
                x=1;
                continue;
            }
           // cout<<stk[tmp1].top()<<"  "<<stk[tmp2].top()<<endl;
            if(stk[tmp1].top()>stk[tmp2].top())
            {
                x=1;
                continue;
            }
            int tmp;
            tmp=stk[tmp1].top();
            stk[tmp1].pop();
            stk[tmp2].push(tmp);

        }

        if(x==1)
            cout<<"illegal"<<endl;
        else
            cout<<"legal"<<endl;


}
 return 0;
}
