#include<bits/stdc++.h>

using namespace std;
map<double, string> str;
int main()
{
    std::ios::sync_with_stdio(false);
    str[0]="Howard";
    str[1]="Sheldon";
    str[2]="Leonard";
    str[3]="Penny";
    str[4]="Rajesh";
    str[5]="Howard";

    double n;
    cin >> n;
    double sum = 0;
    for(int i = 0;; i++)
    {
        if(sum + pow(2, i) * 5 > n)
        {
            cout<<str[ceil((n - sum)/pow(2,i))]<<endl;
            break;
        }
        else
        sum+=pow(2, i) * 5;
    }
    return 0;
}