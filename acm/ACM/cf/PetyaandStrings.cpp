#include <bits/stdc++.h>

using namespace std;

int main()
{
    string str1;
    string str2;
    cin >> str1;
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    cin >> str2;
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    if (str1 > str2)
        cout << "1" << endl;
    else if (str1 < str2)
        cout << "-1" << endl;
    else
        cout << "0" << endl;
}