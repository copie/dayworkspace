#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    long long int n;
    //  long long int sum = 0;
    cin >> n;
    if (n % 2 == 0)
        cout << n / 2 << endl;
    else
        cout << -(n + 1) / 2 << endl;
    return 0;
}