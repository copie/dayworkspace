#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
using namespace std;
struct node{
    string qianbi;
    double rates;
};
int main()
{

    int n;
    while(cin>>n,n)
    {
        map<string,vector<node> > mymap;
        map<string,double> d;
        for(int i=0;i<n;i++)
        {
            string tmp;
            cin>>tmp;
            d[tmp]=0xc0c0c0c0;
        }
        int m;
        cin>>m;
        for(int i=0;i<m;i++)
        {
            double r;
            string f,s;
            cin>>f>>r>>s;
            node tmp;
            tmp.qianbi = s;
            tmp.rates = r;
            mymap[f].push_back(tmp); 
        }

        bool flag = false;
        for (map<string,vector<node> >::iterator it = mymap.begin(); it != mymap.end(); it++)
        {
            queue<string>Q;
            int xx[40];//判断节点是否在队中
            int chi[40];//表示这个节点被访问的次数
            // memset(d,0xc0c0c0c0,sizeof(d));
            for(map<string,double>::iterator tt=d.begin();tt !=d.end();tt++ )
            {
                 tt->second=0xc0c0c0c0;
            }
            memset(xx,INF,sizeof(xx));
            memset(chi,0,sizeof(chi));
            Q.push(it->second.f);
            d[it->second.f]=1.0;
            xx[1]=0;
            chi[1]++;
            while(true)
            {
                int tmp=Q.front();
                Q.pop();
                xx[tmp]=INF;
                for(unsigned int i=0;i<mymap[tmp].size();i++)
                {
                    if(mymap[tmp][i].r*d[tmp]>d[mymap[tmp][i].s])
                    {
                        ;
                    }
                }
            }
    
    
        }
    
    }
}