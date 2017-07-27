#include<iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
string a;
int n;
map<string,int> str;
map<string,int>::iterator it;
cin >> n;
while (n--)
{
cin >> a;
if (str.find(a)!=str.end())
{
cout << a << str[a] << endl;
str[a]++;
continue;
}
str[a]++;
cout << "OK" << endl;
}
return 0;
}
