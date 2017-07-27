#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int Mod = 1e9 + 7;
int a[3000020];
int b[250005];
int c[230005];
int main()
{
    long long int n;
    while (~scanf("%lld", &n))
    {
        long long int ans = 0, sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        sort(b + 1, b + n + 1);
        for (int i = n; i > 0; i--)
        {
            if (a[i] - i >= ans)
                ans = a[i] - i;
            c[i] = ans;
        }

        int maxx = -99999999;
        for (int i = 1; i <= n; i++)
        {
            if (c[b[i]] > maxx)
                a[n + i] = c[b[i]];
            else
                a[n + i] = maxx;
            if (a[n + i] - n - i > maxx)
                maxx = a[n + i] - n - i;
            sum += a[n + i];
            if (sum >= Mod)
                sum %= Mod;
        }
        printf("%lld\n", sum);
    }
    return 0;
}