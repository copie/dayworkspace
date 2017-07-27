#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    string str1, str2;
    cin >> str1;
    cin>>str2;

    vector<int> ans;

    for (int i = 0; i < n; i++)
        ans.push_back(i);
    for (int i = 0; i < m - n + 1; i++)
    {
        // cout<<i<<endl;
        vector<int> nans;
        for (int j = 0; j < n; j++)
        {
            if (str1[j] != str2[i + j])
                nans.push_back(j);
        }
        if (nans.size() < ans.size())
        {
            ans = nans;
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] + 1 << " ";
    cout << endl;
    return 0;
}