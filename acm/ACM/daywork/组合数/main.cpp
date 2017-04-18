#include <iostream>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <set>

using namespace std;
int a[10]={0};
int c;
int n,m;
int b[10];
int j=0;
bool sorted (int * first,int *last)
{
  if (first==last) return true;
  int * next = first;
  while (++next!=last) {
    if (*next>*first)
      return false;
    ++first;
  }
  return true;
}

void fun(void)
{
    if(c==m)
    {   if(sorted(b,b+m)==true)
       {
           for(int i=0;i<m;i++)
        {
            cout<<b[i];
        }
        cout<<endl;

       }

        return;

    }

    for(int i=n;i>=1;i--)
    {
        if(a[i]!=1)
        {
            c++;
            a[i]=1;
            b[j]=i;
            j++;
            fun();
            c--;
            a[i]=0;
            j--;
        }


    }

}
int main()
{
    int N;



       while(cin>>n>>m)
       {
        a[0]=10;
        fun();
       }
    return 0;
}
