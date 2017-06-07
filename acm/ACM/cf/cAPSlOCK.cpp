#include<iostream>

using namespace std;
bool panda(string str)
{
    for(int i=1;i<str.length();i++)
    {
        if(!('A'<=str[i]&&str[i]<='Z'))
        return false;
    }
    return true;
}
int main()
{
    string str;
    cin>>str;
    if('a'<=str[0]&&str[0]<='z')
    {
        if(panda(str))
        {
            for(int i=0;i<str.length();i++)
            {
                if(i==0)
                cout<<char(str[i]-('a'-'A'));
                else
                cout<<char(str[i]+('a'-'A'));
            }
        }
        else
        {
            cout<<str<<endl;
        }
    }else
    {
        if(panda(str))
        {
            for(int i=0;i<str.length();i++)
            {
                cout<<char(str[i]+('a'-'A'));
            }
        }
        else{
            cout<<str;
        }
    }
    cout<<endl;
}