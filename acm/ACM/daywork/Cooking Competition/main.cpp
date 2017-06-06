#include <iostream>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        int a=0,b=0;
        while(n--)
        {
            int t;
            cin>>t;
            if(t==1)
                a++;
            if(t==2)
                b++;
            if(t==3)
            {
                a++;
                b++;
            }
            if(t==4)
            {
                a--;
                b--;
            }
        }
        if(a>b)
        cout<<"Kobayashi"<<endl;
        else if(b>a)
            cout<<"Tohru"<<endl;
        else
            cout<<"Draw"<<endl;

    }
    return 0;
}
