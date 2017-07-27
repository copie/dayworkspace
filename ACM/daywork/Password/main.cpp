#include <iostream>

using namespace std;
struct team
{
    string str1;
    string str2;
    int f=0;
}myteam[10000];
int main()
{
    int n;
    cin>>n;
    int m=0;
    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;
        myteam[i].str1=str;
        str.clear();
        cin>>str;
        for(auto& c:str)
        {
            if(c=='1')
            {
                c='@';
                myteam[i].f=1;
            }
            if(c=='0')
            {
                c='%';
                myteam[i].f=1;
            }
            if(c=='l')
            {
                c='L';
                myteam[i].f=1;
            }
            if(c=='O')
            {
                c='o';
                myteam[i].f=1;
            }
            myteam[i].str2=str;
        }
        if(myteam[i].f==1)
        m++;

    }
    if(m!=0)
    cout<<m<<endl;
    for(auto s:myteam)
    {
        if(s.f==1)
        {
            cout<<s.str1<<" "<<s.str2<<endl;
        }
    }
    if(m==0&&n!=1)
        cout<<"There are "<<n<<" accounts and no account is modified"<<endl;
     else if(n==1)
        cout<<"There is "<<n<<" account and no account is modified"<<endl;
    return 0;
}
