#include <stdio.h>
#include <string.h>

int w1;
int n,a,b,L,R;
int fff=0;
int next1[1000009];
int sum=0;
char sumstr[1000009];
char x[1000009];
int cc;
inline int getw(int i)
{
    if(i==0)
    {
        w1=b;
        return w1;
    }
    else
    {
       w1 = (w1+a)%n;
       return w1;
    }
}
inline void Next(char b[])
//部分匹配表的实现
{
    int i,j;
    i=0;
    j=-1;
    next1[i]=j;   //匹配表初值
    while(i<strlen(b))
    {
        if(j==-1||b[i]==b[j])
        {
            i++;
            j++;
            next1[i]=j;
        }
        else
            j=next1[j];
    }
    return ;
}

inline int KMP(char a[],char b[])//kmp匹配算法
{
    int i,j;
    i=j=0;
    Next(b);//先计算部分匹配表
    while(i<sum)
    {
        if(j==-1||a[i]==b[j])
        {

            i++;
            j++;
            if(j==cc)
              fff++;//找到目标字符串，返回到主程序。
        }
        else
            j=next1[j];//a[i]与b[j]不匹配，查表需要跳过的字符个数。
    }
    return -1;//没有找到返回-1
}
int main()
{
    scanf("%d%d%d%d%d",&n,&a,&b,&L,&R);
    for(int i=0;i<n;i++)
    {
        getw(i);
        if((L<=w1&&w1<=R))
        {
            if(w1%2==0)
            sumstr[sum]='A';
            else
            sumstr[sum]='T';

            sum++;
        }
        else
        if((L>w1||w1>R))
        {
            if(w1%2==0)
            sumstr[sum]='G';
            else
            sumstr[sum]='C';
            sum++;
        }
    }
    sumstr[sum]=0;
    scanf("%s",x);
    cc=strlen(x);
    KMP(sumstr,x);
    printf("%d\n",fff);

    return 0;
}
