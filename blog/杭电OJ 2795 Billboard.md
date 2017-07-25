# 杭电OJ 2795 Billboard

## Problem Description

At the entrance to the university, there is a huge rectangular billboard of size h*w (h is its height and w is its width). The board is the place where all possible announcements are posted: nearest programming competitions, changes in the dining room menu, and other important information.

On September 1, the billboard was empty. One by one, the announcements started being put on the billboard.

Each announcement is a stripe of paper of unit height. More specifically, the i-th announcement is a rectangle of size 1 * wi.

When someone puts a new announcement on the billboard, she would always choose the topmost possible position for the announcement. Among all possible topmost positions she would always choose the leftmost one.

If there is no valid location for a new announcement, it is not put on the billboard (that's why some programming contests have no participants from this university).

Given the sizes of the billboard and the announcements, your task is to find the numbers of rows in which the announcements are placed.

## Input

There are multiple cases (no more than 40 cases).

The first line of the input file contains three integer numbers, h, w, and n (1 <= h,w <= 10^9; 1 <= n <= 200,000) - the dimensions of the billboard and the number of announcements.

Each of the next n lines contains an integer number wi (1 <= wi <= 10^9) - the width of i-th announcement.

## Output

For each announcement (in the order they are given in the input file) output one number - the number of the row in which this announcement is placed. Rows are numbered from 1 to h, starting with the top row. If an announcement can't be put on the billboard, output "-1" for this announcement.

## Sample Input

    3 5 5
    2
    4
    3
    3
    3
## Sample Output

    1
    2
    1
    3
    -1

最开始的时候没有发现这是一个线段树的问题，结果开了一个亿的数组尴尬死了

    ## AC代码
    
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

