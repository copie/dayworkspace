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
    int n;
    cin>>n;
    while(n--)
    {
        string str;
        cin>>str;
        // cout<<str<<endl;
        int dp1[200],dp2[200];
        memset(dp1,0,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        dp1[0]=0;
        dp2[0]=1;
        for(int i = 0;i<str.length();i++)
        {
            if(str[i]>='a'&&str[i]<='z')
            {
                dp1[i+1]=min(dp1[i]+1,dp2[i]+2);
                dp2[i+1]=min(dp1[i]+2,dp2[i]+2);
            }
            else
            {
                dp1[i+1]=min(dp1[i]+2,dp2[i]+2);
                dp2[i+1]=min(dp1[i]+2,dp2[i]+1);
            }

        }
        cout<<min(dp1[str.length()],dp2[str.length()]+1)<<endl;
    }
    return 0;
}