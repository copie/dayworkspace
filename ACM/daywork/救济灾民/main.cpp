#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

int main()
{
   int x;
   cin>>x;
   while(x--)
   {
      double sum=0;
      map<double,double> commodity;
      double n,m;
      cin>>n>>m;
      for(double i=0;i<m;i++)
      {
          double tmp;
          cin>>tmp;
          cin>>commodity[tmp];
      }
       map<double,double>::iterator it;
       it=commodity.begin();
       while(it!=commodity.end())
      {
          if(n>it->first*it->second)
          {
              n-=it->first*it->second;
              sum+=it->second;
          }
          else
          {
              sum+=n/it->first;
              break;
          }
          it++;
      }
      cout<<setiosflags(ios::fixed)<<setprecision(2)<<sum<<endl;
   }
    return 0;
}
