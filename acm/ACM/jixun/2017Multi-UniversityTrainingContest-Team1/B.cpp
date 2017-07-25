#include <bits/stdc++.h>

using namespace std;

int a[27][100010];
int b[27];
int main()
{
    int n;
    while (cin >> n)
    {
        char str[1000010];
        scanf("%s", str);
        for (int i = 0; i < strlen(str); i++)
        {
            a[str[i] - 'a' + 1][i]++;
        }
        int x=25;
        int tmp=-1;
        int tmp2;
        for(int i=0;i<strlen(str);i++)
        {
            for(int j=1;j<int('a');j++)
            {
                if(a[i][j]>tmp)
                {
                    tmp2=i;
                }

            }
        }
    }
    return 0;
}

