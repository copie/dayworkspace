#include <iostream>
#define MAX 1000010

using namespace std;

int array[MAX];
int segTree[MAX * 4 + 10];

void buildtree(int node,int begin,int end)
{
    if(begin==end)
    {
        segTree[node]=array[begin];
    }
    else
    {
        buildtree(node*2,begin,(end+begin)/2);
        buildtree(node*2+1,(end+begin)/2+1,end);
        segTree[node]=segTree[node*2]+segTree[node*2+1];

    }
}
int query(int node, int begin, int end, int left, int right)
{
    if(begin==left&&end==right)
    {
        return segTree[node];
    }
    int mid;
    mid=(begin+end)/2;
    if(right<=mid)
         return query(node * 2, begin, mid, left, right);
    else if(left>mid)
         return query(node*2+1,mid+1,end,left,right);
    else return query(node * 2, begin, mid, left, right)+query(node*2+1,mid+1,end,left,right);
}
int main()
{
    int M,N;
    cin>>N>>M;
    for(int i=1;i<=N;i++)
        cin>>array[i];
    buildtree(1,1,N);
    int left,right;
    while(M--)
    {
        cin>>left>>right;
        cout<<query(1,1,N,left,right);
    }



    return 0;
}
