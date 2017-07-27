#include<bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    double k, n;
    cin >> k >> n;
    if( ceil(k/2)>= n)
        cout <<std::fixed<<(long long int)(2 * n - 1)<< endl;
    else
    {
        cout<<std::fixed<<(long long int)(n-ceil(k/2))*2<<endl;
    }
    return 0;
}