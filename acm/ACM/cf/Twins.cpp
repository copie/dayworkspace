#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    double sum = 0;
    double a[10000];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a + n);
    double tmp = 0;
    int x = 0;
    for (int i = n - 1; i >= -1; i--)
    {

        if (tmp <= sum / 2)
        {
            tmp += a[i];
            x++;
        }
        else
        {
            cout << x << endl;
            return 0;
        }
    }
}