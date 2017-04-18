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
map<char,double> lpri;
map<char,double> rpri;

int Smax(int a,int b)
{
    stringstream ss;
    int x=0;
    int y=0;
    //cout<<"\n"<<a<<"a    b"<<b<<endl;
    string str;
    ss<<a;
    ss>>str;
    for(int i=0;i<str.length();i++)
        x+=str[i]-'0';
    ss.clear();
    str.clear();
    ss<<b;
    ss>>str;
    for(int i=0;i<str.length();i++)
       y+=str[i]-'0';
    return max(x,y);

}
int main()
{
     lpri['=']=0;
     lpri['(']=1;
     lpri[',']=1.5;
     lpri['+']=3;
     lpri['-']=3;
     lpri['*']=5;
     lpri['/']=5;
     lpri[')']=6;

     rpri['=']=0;
     rpri['(']=6;
     rpri[',']=2.5;
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
         str+='=';
         op.push('=');
         string tmpnum;
        // cout<<str<<endl;
         for(unsigned int i=0;i<str.length();i++)
         {   if(str[i]=='S'||str[i]=='m'||str[i]=='a'||str[i]=='x')
             continue;
             //cout<<str[i]<<endl;
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
             //cout<<postexp1.top();
             postexp.pop();
         }
         while(!postexp1.empty())
         {   //cout<<postexp1.top()<<" ";
             double num,num1;
             stringstream ss;
             if(postexp1.top()==",")
             {
                 num=postexpnum.top();
                 postexpnum.pop();
                 num1=postexpnum.top();
                 postexpnum.pop();
                 num=Smax(num,num1);
                // cout<<"\n"<<num<<"   num"<<endl;
                 postexpnum.push(num);
             }
             else if(postexp1.top()=="+")
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
                 num=postexpnum.top()-num;
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
                 num=postexpnum.top()/num;
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
          //cout<<postexpnum.top();
          printf("%.0lf\n",postexpnum.top());
          postexpnum.pop();



     }
    return 0;
}
