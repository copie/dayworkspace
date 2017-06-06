#include <math.h>
#include <stdio.h>


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        int sum=1;
        scanf("%d",&n);
        for(int i=1;i<=n-2;i++)
        {
            sum*=n;
            sum%=10003;
        }
        printf("%d\n",sum);


    }
    return 0;
}
