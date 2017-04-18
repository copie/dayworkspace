    #include <iostream>
    #include <stack>
    #include <sstream>

    using namespace std;

    int main()
    {
        int n;
        cin>>n;
        while(n--)
        {
            string str;
            stack<int>qian;
            cin>>str;
            string str1;
            string str2;
            for(int i=str.length()-1;i>=0;i--)
            {
                if(str[i]=='d'||str[i]=='n'||str[i]=='x')
                {
                    if(!str2.empty())
                    {
                        stringstream ss;
                        ss<<str2;
                        int a;
                        ss>>a;
                        str2.clear();
                        qian.push(a);

                    }
                    int tmpnum1;
                    tmpnum1=qian.top();
                    int tmpnum2;
                    qian.pop();
                    tmpnum2=qian.top();
                    qian.pop();
                    if(str[i]=='d')
                    {
                        qian.push(tmpnum1+tmpnum2);


                    }
                    if(str[i]=='n')
                    {
                        qian.push(min(tmpnum1,tmpnum2));
                    }
                    if(str[i]=='x')
                    {
                        qian.push(max(tmpnum1,tmpnum2));
                    }

                    i-=2;
                    continue;
                }
                if(str[i]==','||str[i]=='('||str[i]==')')
                {
                    if(!str2.empty())
                    {
                        stringstream ss;
                        ss<<str2;
                        int a;
                        ss>>a;
                        str2.clear();
                        qian.push(a);

                    }
                    continue;
                }
                if(str[i]>='0'&&str[i]<='9')
                {
                    str2=str[i]+str2;

                }

            }
             if(!str2.empty())
                    {
                        stringstream ss;
                        ss<<str2;
                        int a;
                        ss>>a;
                        str2.clear();
                        qian.push(a);

                    }
            if(cout<<qian.top())
                cout<<endl;

        }
        return 0;
    }
