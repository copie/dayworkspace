#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int sum;
    int s;

    for (int i = 0; i < n; i++)
    {
        int tmp;

        if (i == 0)
        {
            cin >> s;
            sum = 1;
        }
        else
        {
            cin >> tmp;
            if (tmp <= s)
                sum++;
        }
    }
    cout << int(log2(sum)) << endl;
    return 0;
}