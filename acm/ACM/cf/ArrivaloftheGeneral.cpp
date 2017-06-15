#include<iostream>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    cout<<n<<endl;
    int a[1000];
    int mmax = -0x3f3f3f3f;
    int mmin = 0x3f3f3f3f;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        cout<<a[i]<<endl;
        mmax = max(mmax, a[i]);
        mmin = min(mmin, a[i]);
    }
    int x;
    for(int i = 0; i < n; i++)
    {
        if(a[i] == mmax)
        {
            x = i;
            break;
        }
    }
    int y;
    for(int i = n - 1; i >= 0; i--)
    {
        if(a[i] == mmin)
        {
            y = i;
            break;
        }
    }
    if(y > x)
        cout << x + n - y - 1 << endl;
    else
        cout << x + n - y - 2 << endl;

    return 0;
}