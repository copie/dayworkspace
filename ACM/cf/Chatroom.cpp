#include <iostream>
using namespace std;
int main()
{
    string str;
    cin >> str;
    int i = 0;
    int x = 0;
    int n = str.length();
    for (; i < n; i++)
    {
        if (str[i] == 'h')
        {
            x++;
            break;
        }
    }
    i++;
    for (; i < n; i++)
    {
        if (str[i] == 'e')
        {
            x++;
            break;
        }
    }
    i++;
    for (; i < n; i++)
    {
        if (str[i] == 'l')
        {
            x++;
            break;
        }
    }
    i++;
    for (; i < n; i++)
    {
        if (str[i] == 'l')
        {
            x++;
            break;
        }
    }
    i++;
    for (; i < n; i++)
    {
        if (str[i] == 'o')
        {
            x++;
            break;
        }
    }
    if (x == 5)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}