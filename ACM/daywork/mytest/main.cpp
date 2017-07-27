#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <deque>
#include <stack>
#include <vector>

#define INF 0x3f3f3f3f

#define LOCAL

using namespace std;

int main()
{
    #ifdef LOCAL
       ifstream cin("in.txt");
       ofstream cout("out.txt");
    #endif 
    string str;
    getline(cin,str);
    cout<<str;
}