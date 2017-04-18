#include<iostream>
#include<functional>
#include <cstdio>
#include <cstdlib>
#include<queue>
#include<vector>
using namespace std;
struct cmp1
{
    bool operator ()(double &a,double &b)
    {
        return a>b;//最小值优先
    }
};

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        priority_queue<double,vector<double>,cmp1>que1;//最小值优先
        int m;
        cin>>m;
        for(int i=0;i<m;i++)
        {
            double x;
            cin>>x;
            que1.push(x);
        }
        double sum=0;
        while(!que1.empty())
        {
            double x=que1.top();
            que1.pop();
            if(!que1.empty())
            {
                double y=que1.top();
                que1.pop();
                sum+=x+y;
                que1.push(x+y);
            }
        }
        printf("%.0f\n",sum);

    }
}

