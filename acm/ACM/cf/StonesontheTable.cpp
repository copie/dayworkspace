#include<iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    char c;
    int sum=0;
    for(int i=0;i<n;i++)
    {
        char tmp;
        if(i==0)
        cin>>c;
        else
        {
            cin>>tmp;
            if(tmp==c)
            sum++;
            else
            {
                c=tmp;
            }
        }
    }
    cout<<sum<<endl;
}