#include <iostream>

using namespace std;

int main()
{
    while(true)
    {
    string str;
    getline(cin,str);
    if(cin.eof()) break;
    while(str.find("you")!= string::npos)
    {
        int x=str.find("you");
        string str1=str.substr(0,x);
        string str2=str.substr(x+3);
        str=str1+"we"+str2;
    }
    cout<<str<<endl;
    }
    return 0;
}
