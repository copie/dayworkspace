#include<iostream>
#include<stack>

using namespace std;
stack<int> st;
int main()
{
    int n;
    int t;
    cin >> n >> t;
    string str;
    cin >> str;
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < str.length()-1; j++)
        {
            if(str[j]<str[j+1])
            {
                st.push(j);
                st.push(j + 1);
            }
        }
        while(!st.empty())
        {
            char c;
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            c = str[a];
            str[a] = str[b];
            str[b] = c;
        }
    }
    cout << str << endl;
    return 0;
}