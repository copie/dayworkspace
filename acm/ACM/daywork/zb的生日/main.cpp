#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
using namespace std;
int a[21];
int allmax,allsum;
void dfs(int sum,int i)
{
if(i<0)
return ;
int p=abs(allsum-2*sum);
if(allmax>p)
allmax=p;
dfs(sum+a[i],i-1);
dfs(sum,i-1);
}
int main()
{
int n;
freopen("1.txt", "r", stdin);
while(~scanf("%d",&n))
{
memset(a,0,sizeof(a));
for(int i=0; i<n; i++)
{
scanf("%d",&a[i]);
allsum+=a[i];
}
allmax=9999999;
dfs(0,n-1);
printf("%d\n",allmax);
allsum=0;
}
}
