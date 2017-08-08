#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, m;
        cin >> n >> m;
        if (n * (n - 1) / 2 <= m)
        {
            cout << n * (n - 1) << endl;
            continue;
        }
        long long ans = n * (n - 1);
        if (m >= (n - 1))
        {
            ans += 2 * (n * (n - 1) / 2 - m);
        }
        else
        {
            ans = 2 * m * m + (m * n + n * n) * (n - 1 - m);
        }

        cout << ans << endl;
    }
}