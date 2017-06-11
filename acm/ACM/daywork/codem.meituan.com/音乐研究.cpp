#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[1005], b[1005];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> a[i];

    int minx = 0x3f3f3f3f;
    for (int i = 0; i < m - n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += (a[j + i] - b[j]) * (a[j + i] - b[j]);
        }
        cout << "chen" << endl;
        minx = min(sum, minx);
    }
    cout << minx << endl;
    return 0;
}