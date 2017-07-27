#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
struct node {
int num;
string str;

}DNA[110];
bool cmp(node a,node b)
{
    return a.num<b.num;
}
int main()
{
   int n,m;
   cin>>n>>m;
   int shu[5060];
   for(int i=0;i<m;i++)
   {
        string str;
        cin>>str;
        int ni=0;
        int c=0,g=0,t=0;
        for(int j=0;j<n;j++)
        {
            if(str[j]=='T') t++;
            if(str[j]=='G') ni+=t,g++;
            if(str[j]=='C') ni+=t+g,c++;
            if(str[j]=='A') ni+=t+g+c;
        }
        DNA[i].num=ni;
        DNA[i].str=str;
   }
   sort(DNA,DNA+m,cmp);
   for(int i=0;i<m;i++)
   cout<<DNA[i].str<<endl;
}
