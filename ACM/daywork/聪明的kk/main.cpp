#include<stdio.h>
#include<string.h>
int main(void)
{
    int n,m;
    int sum[21][21];
    int i,j,temp;
    scanf("%d%d",&n,&m);
    memset(sum,0,sizeof(sum));
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            scanf("%d",&temp);
            sum[i][j]= sum[i-1][j]>sum[i][j-1]? (sum[i-1][j]+temp):(sum[i][j-1]+temp);
        }
    }
    printf("%d\n",sum[n][m]);
}
