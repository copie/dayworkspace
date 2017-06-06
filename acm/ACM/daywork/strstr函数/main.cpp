#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    char strOne[100010];
    char strTwo[100010];
    char tmp[200020];
    while(scanf("%s %s",strOne,strTwo)!=EOF)
    {
           // cout<<strOne<<"  "<<strTwo<<endl;
            strcat(tmp,strOne);
            strcat(tmp,strOne);
            char *ptr;
            ptr = strstr(tmp, strTwo);
            if(ptr!=NULL)
            {
                cout << "yes" <<endl;
            }
            else
            {
                cout<<"no"<<endl;
            }
    }

    return 0;
}
