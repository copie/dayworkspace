#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    while(cin>>n)
    {
        vector<int>vec[10009];


        for(int i=1;i<n;i++)
        {
           int x,y;
           cin>>x>>y;
           vec[x].push_back(y);
           vec[y].push_back(x);
        }
        int sum=0;
        for(int i=1;i<=n;i++)
          {
              if(vec[i].size()==1)
                sum++;
          }
          if(sum%2==0)
            cout<<sum/2<<endl;
          else
            cout<<sum/2+1<<endl;
    }
    return 0;
}
