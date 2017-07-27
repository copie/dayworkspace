//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \|     |// '.
//                 / \|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \  -  /// |     |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    int black_nums=0;
    int mini=1024,maxi=-1,minj=1024,maxj=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            char c;
            cin>>c;
            if(c=='B')
            {
                black_nums++;
                mini=min(mini,i);
                minj=min(minj,j);
                maxi=max(maxi,i);
                maxj=max(maxj,j);
            }
        }
    }
    if(black_nums==0)
    {
        cout<<1<<endl;
    }
    else
    {
        maxi++;
        maxj++;
        int l=max(maxi-mini,maxj-minj);
        if(l<=m&&l<=n)
        {
            cout<<l*l-black_nums<<endl;
        }
        else
        {
            cout<<-1<<endl;
        }
    }
    return 0;
}