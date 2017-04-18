#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    double a,b;

    while(n--)
    {
        int bian;
        cin>>bian;
        a=180-360/bian;
        cin>>bian;
        b=180-360/bian;
        for(int i=0;;i++)
        {
            if(a*i>360)
            {
                cout<<"No"<<endl;
                break;
            }
            if((360-a*i)/b==int((360-a*i)/b))
            {
                cout<<"Yes"<<endl;
                break;
            }
        }
    }
}
