#include<iostream>

using namespace std;

int main()
{
    string str;
    cin>>str;
    int sum=0;
    char tmp=str[0];
    for(auto c : str)
    {
        if(c==tmp)
        sum++;
        else{
            sum=1;
            tmp=c;
        }
        if(sum>=7)
        {
             cout<<"YES"<<endl;
             return 0;
        }
       
    }
    cout<<"NO"<<endl;
}