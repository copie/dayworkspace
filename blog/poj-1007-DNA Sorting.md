# poj-1003-DNA Sorting

## 作者语

深知自己的代码能力太差，开始在poj水第三题

## Description

One measure of ``unsortedness'' in a sequence is the number of pairs of entries that are out of order with respect to each other. For instance, in the letter sequence ``DAABEC'', this measure is 5, since D is greater than four letters to its right and E is greater than one letter to its right. This measure is called the number of inversions in the sequence. The sequence ``AACEDGG'' has only one inversion (E and D)---it is nearly sorted---while the sequence ``ZWQM'' has 6 inversions (it is as unsorted as can be---exactly the reverse of sorted). 

You are responsible for cataloguing a sequence of DNA strings (sequences containing only the four letters A, C, G, and T). However, you want to catalog them, not in alphabetical order, but rather in order of ``sortedness'', from ``most sorted'' to ``least sorted''. All the strings are of the same length. 

## Input

The first line contains two integers: a positive integer n (0 < n <= 50) giving the length of the strings; and a positive integer m (0 < m <= 100) giving the number of strings. These are followed by m lines, each containing a string of length n.

## Output

Output the list of input strings, arranged from ``most sorted'' to ``least sorted''. Since two strings can be equally sorted, then output them according to the orginal order.

## Sample Input

    10 6
    AACATGAAGG
    TTTTGGCCAA
    TTTGGCCAAA
    GATCAGATTT
    CCCGGGGGGA
    ATCGATGCAT

## Sample Output

    CCCGGGGGGA
    AACATGAAGG
    GATCAGATTT
    ATCGATGCAT
    TTTTGGCCAA
    TTTGGCCAAA
## AC代码

    #include <iostream>
    #include <algorithm>

    using namespace std;
    struct node {
    int num;
    string str;

    }DNA[110];
    bool cmp(node a,node b)
    {
        return a.num<b.num;
    }
    int main()
    {
    int n,m;
    cin>>n>>m;
    int shu[5060];
    for(int i=0;i<m;i++)
    {
            string str;
            cin>>str;
            int ni=0;
            int c=0,g=0,t=0;
            for(int j=0;j<n;j++)
            {
                if(str[j]=='T') t++;
                if(str[j]=='G') ni+=t,g++;
                if(str[j]=='C') ni+=t+g,c++;
                if(str[j]=='A') ni+=t+g+c;
            }
            DNA[i].num=ni;
            DNA[i].str=str;
    }
    sort(DNA,DNA+m,cmp);
    for(int i=0;i<m;i++)
    cout<<DNA[i].str<<endl;
    }

## 总结

+ 这一题 "Time Limit Exceeded" 多次

- 原因就是逆序数用的是暴力，用队列数组实现对顺序的保存导致超时
***
        int ni=0;
        int c=0,g=0,t=0;
        for(int j=0;j<n;j++)
        {
            if(str[j]=='T') t++;
            if(str[j]=='G') ni+=t,g++;
            if(str[j]=='C') ni+=t+g,c++;
            if(str[j]=='A') ni+=t+g+c;
        }
这个代码针对本题有很大的优化因为元素比较少
***
由于sort排序不是稳定的所以要重写CMP函数保证稳定

本题通过排序竟然比我用下标的方法结合队列速度来的快说明STL里的数据结构效率太低了

***

逆序数：

一个数列中逆序对的总数

逆序对：

设 A 为一个有 n 个数字的有序集 (n>1)，其中所有数字各不相同。
如果存在正整数 i, j 使得 1 ≤ i ＜ j ≤ n 而且 A[i] ＞ A[j]，则 <A[i], A[j]> 这一个有序对称为 A 的一个逆序对，也称作逆序。逆序对的数量称作逆序数。
例如：数组 <2,3,8,6,1> 的逆序对为：<2,1> <3,1> <8,1> <8,6> <6,1> 共5个逆序对。
对于<2,1>:1 ≤ 1 ＜ 5 ≤ 5 ,A[1] ＞ A[5],所以<A[1],A[5]>为一个合法的逆序对。
目前求逆序对数目比较普遍的方法是利用归并排序做到 O(nlog n)的时间复杂度。
当然，也可以利用树状数组、线段树来实现这种基础功能。复杂度均为 O(nlog n)。