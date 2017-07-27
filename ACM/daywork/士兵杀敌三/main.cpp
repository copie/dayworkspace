#include<bits/stdc++.h>

#define MAX 1000010

using namespace std;
struct node1
{
    int ma;
    int mi;
}segtree[MAX*4+10];
int array1[MAX];
void buildtree(int node ,int begin, int end)
{
    if(begin==end)
    {
        segtree[node].ma=array1[begin];
        segtree[node].mi=array1[end];
        return;
    }
    else
    {
        buildtree(node*2,begin,(end+begin)/2);
        buildtree(node*2+1,(end+begin)/2+1,end);
        segtree[node].ma=max(segtree[2*node].ma,segtree[2*node+1].ma);
        segtree[node].mi=min(segtree[2*node].mi,segtree[2*node+1].mi);
    }


}
struct node1 query(int node, int begin, int end, int left, int right)
{
    if(begin==left&&end==right)
    {
        return segtree[node];
    }
    int mid;
    mid=(begin+end)/2;
    if(right<=mid)
         return query(node * 2, begin, mid, left, right);
    else if(left>mid)
         return query(node*2+1,mid+1,end,left,right);
    //else return query(node * 2, begin, mid, left, mid)+query(node*2+1,mid+1,end,mid + 1,right);
    else
    {
        struct node1 tmp1 = query(node * 2, begin, mid, left, mid);
        struct node1 tmp2 = query(node*2+1,mid+1,end,mid + 1,right);
        tmp1.ma = max(tmp1.ma,tmp2.ma);
        tmp1.mi = min(tmp1.mi,tmp2.mi);
       //cout<<tmp1.mi<<"  "<<tmp1.ma<<endl;
        return tmp1;

    }
}
int main()
{
    int M,N;
    cin>>N>>M;
    for(int i=1;i<=N;i++)
        scanf("%d",&array1[i]);
    buildtree(1,1,N);
   // for(int i=0;i<=10;i++)
       // cout<<segtree[i].ma<<"   "<<segtree[i].mi<<endl;
    int left,right;
    while(M--)
    {
        scanf("%d%d",&left,&right);
        struct node1 tmp = query(1,1,N,left,right);
        printf("%d\n",tmp.ma-tmp.mi);
    }



    return 0;
}
