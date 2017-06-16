#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int a[2], n;
    cin >> a[0] >> a[1] >> n;
    int i;
    for(i = 0; n; i++)
    {
        n = n - __gcd(n, a[i % 2]);
    }
    cout << (i + 1) % 2 << endl;
    return 0;
}