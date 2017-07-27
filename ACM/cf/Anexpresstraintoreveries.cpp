#include <iostream>
#include <algorithm>

using namespace std;
int que(int c[], int n)
{
    for (int i = 1; i <= n; i++)
    {

        if (c[i] == 0)
        {
            // cout << i << endl;
            return i;
        }
    }
    return -1;
}
int findque(int a[], int b[], int begin, int n)
{
    for (int i = begin; i < n; i++)
    {
        if (a[i] != b[i])
            return i;
    }
    return -1;
}
int find2(int n, int c[])
{
    for (int i = 1; i <= n; i++)
    {
        if (c[i] == 2)
        {
            // cout << i << endl;
            return i;
        }
    }
    return -1;
}
int main()
{
    int n;
    cin >> n;
    int a[1010], b[1010], c[1010] = {0}, d[1010] = {0};
    for (int i = 0; i < 2 * n; i++)
    {
        if (i < n)
        {
            cin >> a[i];
            c[a[i]]++;
        }
        else
        {
            cin >> b[i - n];
            d[b[i - n]]++;
        }
    }
    int aque = que(c, n);
    // cout << aque << endl;
    int bque = que(d, n);
    if (aque == bque)
    {
        int tmp = findque(a, b, 0, n);
        a[tmp] = aque;
        cout << a[0];
        for (int i = 1; i < n; i++)
            cout << " " << a[i];
        cout << endl;
        return 0;
    }
    else
    {
        int tmp = find2(n, c);
        // cout << tmp << endl;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != b[i] && a[i] == tmp)
            {
                a[i] = aque;
                break;
            }
        }
        int sum1 = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != b[i])
                sum1++;
        }
        if (sum1 == 1)
        {
            cout << a[0];
            for (int i = 1; i < n; i++)
                cout << " " << a[i];
            cout << endl;
            return 0;
        }
        else
        {
            int tmp = find2(n, d);
            for (int i = 0; i < n; i++)
            {
                if (a[i] != b[i] && b[i] == tmp)
                {
                    b[i] = bque;
                    break;
                }
            }
            cout << b[0];
            for (int i = 1; i < n; i++)
                cout << " " << b[i];
            cout << endl;
            return 0;
        }
    }
    return 0;
}