#include <iostream>
#include <set>

using namespace std;

int main()
{
   int n,m;
   cin>>n>>m;
   set<double> myset;
   while(n--)
   {
       double tmp;
       cin>>tmp;
       myset.insert(tmp);

   }
    while(m--)
    {
      double tmp;
      cin>>tmp;
      if(myset.count(tmp)!=0)
            cout<<"YES"<<endl;
      else
        cout<<"NO"<<endl;
    }
    return 0;
}
