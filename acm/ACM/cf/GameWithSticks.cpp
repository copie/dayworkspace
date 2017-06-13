#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    a = min(a, b);
    if (a % 2 == 0)
        cout << "Malvika" << endl;
    else
        cout << "Akshat" << endl;
    return 0;
}