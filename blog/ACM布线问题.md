# ACM布线问题
## 闲聊

这是一题最小生成树prim算法问题没有坑

## 题目信息

### 描述

南阳理工学院要进行用电线路改造，现在校长要求设计师设计出一种布线方式，该布线方式需要满足以下条件：
1. 把所有的楼都供上电。
2. 所用电线花费最少 

### 输入

第一行是一个整数n表示有n组测试数据。(n<5)

每组测试数据的第一行是两个整数v,e.

v表示学校里楼的总个数(v<=500)

随后的e行里，每行有三个整数a,b,c表示a与b之间如果建铺设线路花费为c(c<=100)。（哪两栋楼间如果没有指明花费，则表示这两栋楼直接连通需要费用太大或者不可能连通）

随后的1行里，有v个整数,其中第i个数表示从第i号楼接线到外界供电设施所需要的费用。( 0<e<v*(v-1)/2 )

（楼的编号从1开始），由于安全问题，只能选择一个楼连接到外界供电设备。

数据保证至少存在一种方案满足要求。

### 输出

每组测试数据输出一个正整数,表示铺设满足校长要求的线路的最小花费。

### 样例输入

    1
    4 6
    1 2 10
    2 3 10
    3 1 10
    1 4 1
    2 4 1
    3 4 1
    1 3 5 6

### 样例输出

    4

### AC代码

    #include <iostream>
    #include <string.h>

    #define INF 0x3f3f3f3f
    #define MAXV  505
    using namespace std;
    int n,e;
    int mymap[MAXV][MAXV];
    int sum=0;
    void Prim(int v)
    {
        int lowcost[MAXV];
        int min;
        int closest[MAXV],k;
        for(int i=1;i<=n;i++)
        {
            lowcost[i]=mymap[v][i];
            closest[i]=v;
        }
        for(int i=2;i<=n;i++)
        {
            min=INF;
            for(int j=1;j<=n;j++)
            {
                if(lowcost[j]!=0&& lowcost[j]<min)
                {
                    min=lowcost[j];
                    k=j;
                }
            }
            sum+=min;
            lowcost[k]=0;
        // cout<<closest[k]<<"  "<<k<<"   "<<min<<endl;
            for(int j=1;j<=n;j++)
            {
                if(mymap[k][j]!=0&&mymap[k][j]<lowcost[j])
                {
                    lowcost[j]=mymap[k][j];
                    closest[j]=k;
                }
            }
        }
    }
    int main()
    {
        int N;
        cin>>N;
        while(N--)
        {
            memset(mymap,INF,sizeof(mymap));
            cin>>n>>e;
            for(int i=1;i<=n;i++)
                mymap[i][i]=0;
            for(int i=1;i<=e;i++)
            {
                int a,b,c;
                cin>>a>>b>>c;
                mymap[a][b]=c;
                mymap[b][a]=c;
            }
            int minf=INF;
            int lou;
            for(int i=1;i<=n;i++)
            {
                int tmp;
                cin>>tmp;
                if(tmp<minf)
                {
                    lou=i;
                    minf=tmp;
                }
            }
        Prim(lou);
        cout<<sum+minf<<endl;
        sum=0;
        }
        return 0;
    }

## 作者语

这一题开始对于Prim算法理解不够首先没有对图进行初始化.

还有就是完了标记我已经找到的点,造成结果错误

