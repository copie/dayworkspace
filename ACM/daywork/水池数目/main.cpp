#include<iostream>

using namespace std;

char map1[110][110];
int m,n;
int  dfs(int i,int j)
{

    if(map1[i][j]=='0'||i<0||i>=m||j<0||j>=n)
        return 0;
    else
    {
        map1[i][j]='0';
        //dfs(i-1,j-1);
        dfs(i-1,j);
        //dfs(i-1,j+1);
        dfs(i,j-1);
        dfs(i,j+1);
       // dfs(i+1,j-1);
        dfs(i+1,j);
        //dfs(i+1,j+1);

    }


}
int main()
{
   int t;
   cin>>t;
    while(t--)
    {
        cin>>m>>n;
        int max=0;
        int i;
        for(i=0;i<m;i++)
            for(int j=0;j<n;j++)
                cin>>map1[i][j];
        for(i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {
                if(map1[i][j]=='1')
                    max++;
                dfs(i,j);

            }
    cout<<max<<endl;
    }

return 0;

}
