#include <bits/stdc++.h>

#define MAX 2000010
using namespace std;

int h, w, n;
int segTree[MAX * 4 + 10];

void buildtree(int node, int begin, int end)
{
    if (begin == end)
    {
        segTree[node] = w;
        return;
    }

    buildtree(node * 2, begin, (end + begin) / 2);
    buildtree(node * 2 + 1, (end + begin) / 2 + 1, end);
    segTree[node] = max(segTree[node * 2], segTree[node * 2 + 1]);
}
void addplan(int node, int begin, int end, int add)
{

    if (begin == end)
    {

        segTree[node] = segTree[node] - add;
        //cout<<end<<endl;
        printf("%d\n", end);
        return;
    }
    if (add <= segTree[node * 2])
    {
        addplan(node * 2, begin, (end + begin) / 2, add);
    }
    else
    {
        addplan(node * 2 + 1, (end + begin) / 2 + 1, end, add);
    }
    segTree[node] = max(segTree[node * 2], segTree[node * 2 + 1]);
}
int main()
{

    while (scanf("%d%d%d", &h, &w, &n) != EOF)
    {
        buildtree(1, 1, (h > n ? n : h));
        for (int i = 0; i < n; i++)
        {
            int tmp;
            // cin >> tmp;
            scanf("%d", &tmp);
            if (tmp <= segTree[1])
                addplan(1, 1, (h > n ? n : h), tmp);
            else
                cout << -1 << endl;
        }
    }
    return 0;
}