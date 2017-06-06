#include <iostream>

using namespace std;

int main()
{
    int n,m,sum=0;
    int x,y;
    cin>>n>>m;int a[10][10]={0};
    for(int i=0;i<n;i++)
    {

        cin>>x>>y;
        x+=3;
        y+=3;
        a[x][y]=1;
    }
    for(int i=0;i<m;i++)
        cin>>x>>y;
    if(a[0][0]&&a[3][0]&&a[6][0])
        sum++;
    if(a[1][1]&&a[3][1]&&a[5][1])
        sum++;
    if(a[2][2]&&a[3][2]&&a[4][2])
        sum++;
    if(a[0][3]&&a[1][3]&&a[2][3])
        sum++;
    if(a[4][3]&&a[5][3]&&a[6][3])
        sum++;
    if(a[2][4]&&a[3][4]&&a[4][4])
        sum++;
    if(a[1][5]&&a[3][5]&&a[5][5])
        sum++;
    if(a[0][6]&&a[3][6]&&a[6][6])
        sum++;
    if(a[0][0]&&a[0][3]&&a[0][6])
        sum++;
    if(a[1][1]&&a[1][3]&&a[1][5])
        sum++;
    if(a[2][2]&&a[2][3]&&a[2][4])
        sum++;
    if(a[3][0]&&a[3][1]&&a[3][2])
        sum++;
    if(a[3][4]&&a[3][5]&&a[3][6])
        sum++;
    if(a[4][2]&&a[4][3]&&a[4][4])
        sum++;
    if(a[5][1]&&a[5][3]&&a[5][5])
        sum++;
    if(a[6][0]&&a[6][3]&&a[6][6])
        sum++;
    cout<<sum<<endl;
    return 0;
}
