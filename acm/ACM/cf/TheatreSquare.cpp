#include <iostream>

using namespace std;

int main()
{
    long long int n, m, a;
    while (cin >> n >> m >> a)
    {
        long long int sum = 0;
        sum += n / a;
        if (n % a != 0)
            sum++;
        long long int sum1 = 0;
        sum1 += m / a;
        if (m % a != 0)
            sum1++;
        cout << sum * sum1 << endl;
    }
}