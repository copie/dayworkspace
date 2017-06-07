#include<iostream>

using namespace std;

int main()
{
    int a[100006]={0};
    int k, l, m, n;
    cin >> k >> l >> m >> n;
    int d;
    cin >> d;
    for (int i = 1; i <= d; i++)
    {
        if(i%k==0||i%l==0||i%m==0||i%n==0)
        {
            a[i] = 1;
        }
    }
    int sum = 0;
    for (int i = 1; i <= d; i++)
    {
        if(a[i]==1)
        {
            sum++;
        } 
    }
    cout << sum << endl;
}