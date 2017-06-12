#include <iostream>
#include <algorithm>

using namespace std;
bool cmp(int a, int b)
{
    string str;
    return a > b;
}
bool pan(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[i - 1])
            return false;
    }
    return true;
}
int main()
{
    int n, k;
    cin >> n >> k;
    int a[300];
    int b[300];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < k; i++)
        cin >> b[i];
    sort(b, b + k, cmp);
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
        {
            a[i] = b[x];
            x++;
        }
    }
    if (pan(a, n))
    {
        cout << "No" << endl;
    }
    else
        cout << "Yes" << endl;
}