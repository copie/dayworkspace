#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        if(n>=10&&n<=13)
        {
           int a[20];
           for(int i=0;i<n;i++)
           {
            cin>>a[i];
           }
           sort(a,a+n);
           if(a[0]==1&&a[1]==1&&a[n-1]>a[n-2])
           {
               int x=0;
               for(int i=1;i<n-1;i++)
               {
                   if(a[i]-a[i-1]>2)
                   {
                       cout<<"No"<<endl;
                       x=1;
                       break;
                   }
               }
               if(x==0)
                cout<<"Yes"<<endl;


           }
           else
            cout<<"No"<<endl;
        }
        else
        {
            string tmp;
            getchar();
            getline(cin,tmp);
            cout<<"No"<<endl;
        }

    }
    return 0;
}
