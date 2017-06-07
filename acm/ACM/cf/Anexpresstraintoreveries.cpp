/*#include<iostream>

using namespace std;

int main()
{
    int n;
    int a;
    int tmp;
    int b;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        if(i==0)
            cin >> a;
        else
            cin >> tmp;
    }
    for (int i = 0; i < n; i++)
    {
        if(i==0)
            cin >> b;
        else
            cin >> tmp;
    }
    int x;
    for (int i = 1; i <= n; i++)
    {
        if(i!=a && i!=b)
        {
            cout << i<<" ";
            x = i;
            break;
        }
    }
    int f = 1;
    for (int i = 1; i <= n; i++)
    {
       if(i==x)
           continue;
        else
        {
            f++;
            if(f==n)
                cout << i << endl;
            else
                cout << i <<" ";
           
        }
    }
}
*/
#include<iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[1010];
    int b[1010];
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        if(a[i]!=b[i])
        {
            if(pan(b[i],a))
            
        }
    }
        for (int i = 1; i < n; i++)
            cout << " " << b[i];
    cout << endl;
}