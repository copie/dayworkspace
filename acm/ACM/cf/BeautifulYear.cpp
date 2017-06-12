#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int a;
    cin >> a;
    a++;
    while (1)
    {
        set<char> se;
        stringstream ss;
        string str;
        ss << a;
        ss >> str;
        for (auto c : str)
        {
            se.insert(c);
        }
        if (se.size() == str.length())
        {
            cout << str << endl;
            return 0;
        }
        else
        {
            a++;
        }
    }
    return 0;
}