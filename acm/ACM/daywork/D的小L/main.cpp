#include <iostream>
#include <string.h>

using namespace std;
int a[10]={0};
int c;
int n,m;
int b[10];
int j=0;
void fun(void)
{
    if(c==m)
    {
        for(int i=0;i<m;i++)
        {
            cout<<b[i];

        }
        cout<<endl;
        return;

    }

    for(int i=1;i<=n;i++)
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
    cin>>N;
    while(N--)
    {
        cin>>n;
        m=n;
        fun();
    }
    return 0;
}
