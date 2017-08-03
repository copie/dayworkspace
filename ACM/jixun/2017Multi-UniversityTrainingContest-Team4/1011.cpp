#include <bits/stdc++.h>

using namespace std;

int main()
{
    map<string, int> nums;
    nums["XXXXXX."] = 0;
    nums[".XX...."] = 1;
    nums["XX.XX.X"] = 2;
    nums["XXXX..X"] = 3;
    nums[".XX..XX"] = 4;
    nums["X.XX.XX"] = 5;
    nums["X.XXXXX"] = 6;
    nums["XXX...."] = 7;
    nums["XXXXXXX"] = 8;
    nums["XXXX.XX"] = 9;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        char mymap[8][25];
        for (int i = 1; i <= 7; i++)
        {
            scanf("%s", mymap[i]);
            // cout<<mymap[i]<<endl;
        }

        // string str1 = "" + mymap[1][2] + mymap[2][4] + mymap[5][4] + mymap[7][2] + mymap[5][1] + mymap[2][1] + mymap[4][2];
        string str1= "";
        str1 += mymap[1][2-1];
        str1 += mymap[2][4-1];
        str1 += mymap[5][4-1];
        str1 += mymap[7][2-1];
        str1 += mymap[5][1-1];
        str1 += mymap[2][1-1];
        str1 += mymap[4][2-1];
        // cout<<str1<<endl;
        cout<< nums[str1];
        // string str2 = "" + mymap[1][2 + 5] + mymap[2][4 + 5] + mymap[5][4 + 5] + mymap[7][2 + 5] + mymap[5][1 + 5] + mymap[2][1 + 5] + mymap[4][2 + 5];
        str1="";
        str1 += mymap[1][2+5-1];
        str1 += mymap[2][4+5-1];
        str1 += mymap[5][4+5-1];
        str1 += mymap[7][2+5-1];
        str1 += mymap[5][1+5-1];
        str1 += mymap[2][1+5-1];
        str1 += mymap[4][2+5-1];
        // cout << str1 << endl;

        cout<< nums[str1]<<":";

        // string str3 = "" + mymap[1][2+13] + mymap[2][4+13] + mymap[5][4+13] + mymap[7][2+13] + mymap[5][1+13] + mymap[2][1+13] + mymap[4][2+13];
        str1="";
        str1 += mymap[1][2+12-1];
        str1 += mymap[2][4+12-1];
        str1 += mymap[5][4+12-1];
        str1 += mymap[7][2+12-1];
        str1 += mymap[5][1+12-1];
        str1 += mymap[2][1+12-1];
        str1 += mymap[4][2+12-1];
        // cout << str1 << endl;

        cout<< nums[str1];

        str1="";
        // string str4 = "" + mymap[1][2+17] + mymap[2][4+17] + mymap[5][4+17] + mymap[7][2+17] + mymap[5][1+17] + mymap[2][1+17] + mymap[4][2+17];
        str1 += mymap[1][2+17-1];
        str1 += mymap[2][4+17-1];
        str1 += mymap[5][4+17-1];
        str1 += mymap[7][2+17-1];
        str1 += mymap[5][1+17-1];
        str1 += mymap[2][1+17-1];
        str1 += mymap[4][2+17-1];
        // cout << str1 << endl;

        cout<<nums[str1]<<endl;
    }

    return 0;
}