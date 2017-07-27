#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int a;
    int b;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
        {
            int t;
            cin >> t;
            if (t == 1)
            {
                a = i;
                b = j;
                cout << abs(3 - j) + abs(3 - i) << endl;
                return 0;
            }
        }
}