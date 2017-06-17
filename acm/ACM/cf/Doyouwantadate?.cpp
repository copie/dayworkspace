#include<bits/stdc++.h>

using namespace std;
long long int biao[400000];

int main()
{
    
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    biao[0]=1;
    for(int i=1;i<=n;i++)
    biao[i]=(biao[i-1])*2%1000000007;
    long long int a[400000];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    long long int sum;
    for(int j = 1; j < n ; j++)
    {
        long long int len = a[j] - a[j - 1];
        long long int cntL = j;
        long long int cntR = n - j;
        long long int add = (biao[cntL] - 1)*(biao[cntR] - 1)%1000000007;

        sum = (sum+(len*add)) % (1000000000 + 7);
       
    }
    cout << sum % (1000000000 + 7) << endl;
    return 0;
}