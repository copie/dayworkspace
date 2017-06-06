#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;
int pan(char c)
{
    switch(c)
    {
        case '0':return 6;
        case '1':return 2;
        case '2':return 5;
        case '3':return 5;
        case '4':return 4;
        case '5':return 5;
        case '6':return 6;
        case '7':return 3;
        case '8':return 7;
        case '9':return 6;
        case 'a':return 6;
        case 'b':return 5;
        case 'c':return 4;
        case 'd':return 5;
        case 'e':return 5;
        case 'f':return 4;
    }
    return 0;
}
int main()
{
int T;
//cin>>T;
scanf("%d",&T);
//char ff[20];
while(T--)
{
    unsigned int n;
    unsigned int sum=0;
    scanf("%d",&n);
    char str[20];
    unsigned int a;
    scanf("%x",&a);
    for(unsigned int i=0;i<n;i++)
    {
        sprintf(str,"%08x",a);
        unsigned int l=strlen(str);
        for(unsigned int j=0;j<l;j++)
        {
            sum+=pan(str[j]);
        }
        a++;
    }
    cout<<sum<<endl;
    sum=0;

}

}
