#include <iostream>
#include <stack>
#include <cstdio>
#include <sstream>

using namespace std;

int main()
{
    string str;
    while(getline(cin,str))

    {    stack<string> postexp1;
         stack<double> postexpnum;
         string str1;
        for(int i=0;i<str.length();i++)
        {
            if(str[i]==' ')
            {
                if(!str1.empty())
                {
                   postexp1.push(str1);
                    //cout<<str1<<endl;
                    str1.clear();
                }
            }
            else
                str1+=str[i];
        }
        if(!str1.empty())
        {
            postexp1.push(str1);
        }
        while(!postexp1.empty())
         {
             double num;
             stringstream ss;
             if(postexp1.top()=="+")
             {
                 num=postexpnum.top();
                 postexpnum.pop();
                 num+=postexpnum.top();
                 postexpnum.pop();
                 postexpnum.push(num);

             }
           else if(postexp1.top()=="-")
             {
                 num=postexpnum.top();
                 postexpnum.pop();
                 num=num-postexpnum.top();
                 postexpnum.pop();
                 postexpnum.push(num);

             }
            else if(postexp1.top()=="*")
             {
                 num=postexpnum.top();
                 postexpnum.pop();
                 num*=postexpnum.top();
                 postexpnum.pop();
                 postexpnum.push(num);

             }
            else if(postexp1.top()=="/")
             {
                 num=postexpnum.top();
                 postexpnum.pop();
                 num=num/postexpnum.top();
                 postexpnum.pop();
                 postexpnum.push(num);


             }
             else
             {
                ss<<postexp1.top();
                ss>>num;
                postexpnum.push(num);
             }

            postexp1.pop();
         }
         //cout<<postexpnum.top()<<endl;
         printf("%.2lf\n",postexpnum.top());
    }

    return 0;
}
