#include <iostream>
#include <stdio.h>
#define N 1000005
using namespace std;
struct node{
    int l,r,sum;
};
node sb[4*N];
int build(int l,int r,int k)
{
    sb[k].l=l;sb[k].r=r;
    if(l==r)
    {
        scanf("%d",&sb[k].sum);
        return sb[k].sum;
    }
    int mid=(r+l)/2;
    sb[k].sum=build(l,mid,k<<1)+build(mid+1,r,k<<1|1);
    return sb[k].sum;
}
int query(int l,int r,int k)
{
    if(l>r) return 0;
    if(l==sb[k].l&&r==sb[k].r)
        return sb[k].sum;
    if(l>=sb[k].l&&r<=sb[k].r)
    {
        int mid=(sb[k].l+sb[k].r)/2;
        if(mid>r)mid=r;
        if(mid<l)mid=l-1;
        return query(l,mid,k<<1)+query(mid+1,r,k<<1|1);
    }
}
int main()
{
    int n,m,l,r;
    cin>>n>>m;
    build(1,n,1);
//    for(int i=0;i<10;i++)
//        cout<<sb[i].l<<' '<<sb[i].r<<' '<<sb[i].sum<<endl;
    while(m--)
    {
        scanf("%d %d",&l,&r);
        printf("%d\n",query(l,r,1));
    }
    return 0;
}
