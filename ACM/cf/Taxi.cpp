#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

map<int, int> mymap;

int main()
{
    int n;
    cin >> n;
    int a;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        mymap[a]++;
    }
    int sum = mymap[4];
    if (mymap[3] > mymap[1])
    {
        mymap[1] = 0;
        sum += mymap[3];
    }
    else
    {
        mymap[1] = mymap[1] - mymap[3];
        sum += mymap[3];
    }
    sum += mymap[2] / 2;
    if (mymap[2] % 2 != 0)
    {
        sum++;
        if (mymap[1] > 2)
        {

            mymap[1] = mymap[1] - 2;
        }
        else
        {
            mymap[1] = 0;
        }
    }
    sum += (mymap[1] + 3) / 4;
    cout << sum << endl;
}