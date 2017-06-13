#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int sum = 0;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        if (b - a >= 2)
            sum++;
    }
    cout << sum << endl;
}