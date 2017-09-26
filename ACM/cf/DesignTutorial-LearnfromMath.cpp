#include <bits/stdc++.h>

using namespace std;
bool pan(int x)
{
    if (x == 2)
        return true;
    for (int i = 2; i < x; i++)
        if (x % i == 0)
            return false;
    return true;
}
int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int x;
    while (1)
    {
        x = rand() % (n - 2) + 2;
        if (!pan(x) && !pan(n - x))
            break;
    }
    cout << x << " " << n - x << endl;
    return 0;
}