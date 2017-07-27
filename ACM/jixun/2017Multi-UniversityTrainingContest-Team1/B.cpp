#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define LC(x) (x<<1)
#define RC(x) ((x<<1)+1)
#define MID(x,y) ((x+y)>>1)
#define fin(name) freopen(name,"r",stdin)
#define fout(name) freopen(name,"w",stdout)
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define FAST_IO ios::sync_with_stdio(false);cin.tie(0);
typedef pair<int, int> pii;
typedef long long LL;
const double PI = acos(-1.0);
const int N = 1e5 + 7;
const LL mod = 1e9 + 7;
LL fac[N];
char s[N];
int ishead[30], maxlen;
 
struct info
{
    char c;
    LL val;
    int f[N];
    void init()
    {
        val = 0LL;
        CLR(f, 0);
    }
    void cal()
    {
        for (int i = 0; i < maxlen; ++i)
        {
            if (f[i] >= 26)
            {
                f[i + 1] += f[i] / 26;
                f[i] %= 26;
            }
        }
    }
    bool operator<(const info &rhs)const
    {
        for (int i = maxlen; i >= 0; --i)
        {
            if (f[i] != rhs.f[i])
                return f[i] < rhs.f[i];
        }
        return 0;
    }

};

info arr[26];
 
void init()
{
    CLR(ishead, 0);
    maxlen = 0;
    for (int i = 0; i < 26; ++i)
        arr[i].init();
}
int main(void)
{
    int i, j, n;
    fac[0] = 1LL;
    for (i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * 26LL % mod;
    int q = 1;
    while (~scanf("%d", &n))
    {
        init();
        for (i = 0; i < n; ++i)
        {
            scanf("%s", s);
            int len = strlen(s);
            if (len > 1)
                ishead[s[0] - 'a'] = 1;
            if (len > maxlen)
                maxlen = len;
            for (j = 0; j < len; ++j)
            {
                int id = s[j] - 'a';
                arr[id].val = (arr[id].val + fac[len - j - 1]) % mod;
                ++arr[id].f[len - j - 1];
            }
        }
        for (i = 0; i < 26; ++i)
        {
            arr[i].c = 'a' + i;
            arr[i].cal();
        }
        int sw = 0;
        for (i = 0; i < 26; ++i)
        {
            if (!ishead[arr[i].c - 'a'] && arr[i] < arr[sw])
                sw = i;
        }
        swap(arr[0], arr[sw]);
        sort(arr + 1, arr + 26);
        LL ans = 0;
        for (i = 0; i < 26; ++i)
        {
            ans = ans + (arr[i].val * (LL)(i)) % mod;
            ans %= mod;
        }
        printf("Case #%d: %lld\n", q++, ans);
    }
    return 0;
}