#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
struct rectangles
{
    int num;
    int l;
    int d;
};
bool cmp(struct rectangles a,struct rectangles b)
{
    if(a.num>b.num)
        return false;
    else if(a.num<b.num)
      return true;
    else if(a.l>b.l)
        return false;
    else if(a.l<b.l)
        return true;
    else if(a.d>b.d)
        return false;
    else if(a.d<b.d)
        return true;
}
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        struct rectangles rectangle[10000];
        int m;
        cin>>m;
        for(int i=0;i<m;i++)
        {
            cin>>rectangle[i].num;
            int tmp1,tmp2;
            cin>>tmp1>>tmp2;

           // cout<<tmp1<<" "<<tmp2<<endl;
            if(tmp1>tmp2)
            {
                rectangle[i].l=tmp1;
                rectangle[i].d=tmp2;
            }
             else
            {
                rectangle[i].l=tmp2;
                rectangle[i].d=tmp1;
            }
        }
        sort(rectangle,rectangle+m,cmp);
        cout<<rectangle[0].num<<" "<<rectangle[0].l<<" "<<rectangle[0].d<<endl;
        for(int i=1;i<m;i++)
        {
            //cout<<(rectangle[i].num!=rectangle[i-1].num&&rectangle[i].l!=rectangle[i-1].l&&rectangle[i].d!=rectangle[i-1].d)<<endl;
             if(!(rectangle[i].num==rectangle[i-1].num&&rectangle[i].l==rectangle[i-1].l&&rectangle[i].d==rectangle[i-1].d))
             cout<<rectangle[i].num<<" "<<rectangle[i].l<<" "<<rectangle[i].d<<endl;
        }
    }
    return 0;
}
