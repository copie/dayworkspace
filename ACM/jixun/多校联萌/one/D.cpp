#include <iostream>
using namespace std;
long long a[50005];
int main(int argc, char *argv[])
{
    long long n, i, ans, max, sum, ans1, min;
    while (cin >> n)
    {
        for (sum = i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += a[i];
        }
        ans = max = a[0];
        for (i = 1; i < n; i++)
        {
            if (max < 0)
                max = 0;
            max += a[i];
            if (ans < max)
                ans = max;
        }
        ans1 = min = a[0];
        for (i = 1; i < n; i++)
        {
            if (min > 0)
                min = 0;
            min += a[i];
            if (ans1 > min)
                ans1 = min;
        }
        if (ans < sum - ans1)
            ans = sum - ans1;
        cout << ans << endl;
    }
    return 0;
}