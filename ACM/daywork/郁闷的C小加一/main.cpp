#include <iostream>
#include <stack>
#include <sstream>
#include <map>
#include <cstdio>
#include <string>
#include <queue>

using namespace std;

stack<char> op;
stack<string> postexp;
stack<string> postexp1;
stack<double> postexpnum;
map<char,int> lpri;
map<char,int> rpri;


int main()
{
     lpri['=']=0;
     lpri['(']=1;
     lpri['+']=3;
     lpri['-']=3;
     lpri['*']=5;
     lpri['/']=5;
     lpri[')']=6;

     rpri['=']=0;
     rpri['(']=6;
     rpri['+']=2;
     rpri['-']=2;
     rpri['*']=4;
     rpri['/']=4;
     rpri[')']=1;
     int N;
     cin>>N;
     while(N--)
     {
         string str;
         cin>>str;
         str=str+'=';
         op.push('=');
         string tmpnum;
        // cout<<str<<endl;
         for(unsigned int i=0;i<str.length();i++)
         {
             if(rpri.count(str[i]))
             {
                 if(tmpnum.length()!=0)
                 {
                    postexp.push(tmpnum);
                    tmpnum.clear();
                 }

                 if(rpri[str[i]]>lpri[op.top()])
                    op.push(str[i]);
                else
                {
                    if(str[i]==')')
                    {
                        while(op.top()!='(')
                        {
                            string str1;
                            str1+=op.top();
                            op.pop();
                            postexp.push(str1);
                        }
                        op.pop();
                    }
                    else
                    {
                        while(lpri[op.top()]>rpri[str[i]])
                       {
                            string str1;
                            str1+=op.top();
                            op.pop();
                            postexp.push(str1);
                        }
                        op.push(str[i]);
                    }
                }
             }
            else
            {
                tmpnum+=str[i];
            }
         }
         while(!postexp.empty())
         {

             postexp1.push(postexp.top());
             postexp.pop();

         }
         while(!postexp1.empty())
         {
            cout<< postexp1.top();
             postexp1.pop();

         }
         cout<<endl;
     }
    return 0;
}
