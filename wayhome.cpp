#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 5e5 + 10;
namespace FastIO {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p1 = buf, p2 = (p1 + fread(buf, 1, 1 << 21, stdin))) == p1 ? EOF : *p1++)
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar((x % 10) ^ '0'); }
	template <typename T> inline void print(T x) { if (x > 0) write<T>(x); else if (x < 0) putchar('-'), write<T>(-x); else putchar('0'); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;
namespace solution
{
    int n,T;
    int d[N],p[N];
    int lst[N],sum[N];
    int cost = 0,val = 0;
    void init()
    {
        for(int i=1;i<=n;i++) lst[i] = n+1;
        stack <int> st;
        for(int i=1;i<=n;i++)
        {
            while(st.size() && p[st.top()] > p[i]){lst[st.top()] = i;st.pop();}
            st.push(i);
            sum[i] = sum[i-1] + d[i];
        }
        sum[n+1] = sum[n];
    }
    void solve()
    {
        n = read<int>(),T = read<int>();
        for(int i=1;i<=n;i++){d[i] = read<int>();p[i] = read<int>();}
        for(int i=1;i<=n;i++) if(d[i] > T) {puts("-1");return;}
        init();
        for(int i=1;i<=n;i++)
        {
            int dist = sum[lst[i]-1] - sum[i-1];
            if(val < dist)
            {
                if(dist > T){cost += p[i]*(T-val);val = T;}
                else {cost += p[i]*(dist - val);val = dist;}
            }
            val -= d[i];
        }
        print(cost,'\n');
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}