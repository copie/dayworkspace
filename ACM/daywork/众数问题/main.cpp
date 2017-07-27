#include <iostream>

using namespace std;

int main()
{

    int N;
    cin>>N;
    while(N--)
    {
         int a[100011]={0};
        int n;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            int tmp;
            cin>>tmp;
            a[tmp]++;
        }
        int c=-1,b;
        for(int i=0;i<100011;i++)
        {
            if(a[i]>c)
            {
                c=a[i];
                b=i;
            }
        }
        cout<<b<<" "<<c<<endl;
    }
}
