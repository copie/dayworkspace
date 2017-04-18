
#include <stdio.h>
#include <string.h>

#define MAX 1000010

int array[MAX]={0};

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
    else return query(node * 2, begin, mid, left, mid)+query(node*2+1,mid+1,end,mid + 1,right);
}
void  addkill(int node,int begin,int end,int add,int i)
{
    if(i>=begin&&i<=end)

    {
         if(begin==end)
    {
        if(begin==i)
        segTree[node]=segTree[node]+add;
    }
    else
    {
        addkill(node*2,begin,(end+begin)/2,add,i);
        addkill(node*2+1,(end+begin)/2+1,end,add,i);
        segTree[node]=segTree[node*2]+segTree[node*2+1];
    }
    }


    return;
}
int main()
{
    int M,N;
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
        scanf("%d",&array[i]);
    buildtree(1,1,N);
    int left,right;
    char instruction[10];
    while(M--)
    {

        scanf("%s %d%d",instruction,&left,&right);
        if(instruction[0]=='A')
            {
                addkill(1,1,N,right,left);

            }
        else
        {
            printf("%d\n",query(1,1,N,left,right));
        }

    }



    return 0;
}
