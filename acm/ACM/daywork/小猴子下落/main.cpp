#include <iostream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    int D,I;
    while(cin>>D>>I,D+I)
    {
        int a[1048579]={0};
        //memset(a,-1,sizeof(a));
        int i=1,j=1;
        for(;i<=I;i++)
        {   j=1;
            while(j<pow(2,D-1))
            {
              //  cout<<a[j]<<endl;
               // cout<<(a[j]==0)<<"  a[j]==0????"<<endl;
                if(a[j]==0)
                {
                     a[j]=100;
                    j=2*j;
                }

                else
                {

                   j=2*j+1;
                   a[j]=0;
                }
               // a[j]=-1*a[j];

            }
        }
       cout<<j<<endl;
    }
    return 0;
}
