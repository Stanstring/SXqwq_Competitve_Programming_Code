#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1e5 + 10;
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
    int n;
    int tot = 0;
    int sum1 = 0,sum2 = 0,sum3 = 0;
    void solve()
    {
        sum1 = sum2 = sum3 = tot = 0;
        n = read<int>();
        int all = 0;
        for(int i=1;i<=n;i++){int t = read<int>();all += t;sum3 += t/3;if(t%3 == 1) sum1 ++;else if(t%3 == 2) sum2 ++;}
        if(sum1 + sum2 * 2 <= sum3) 
        {
            print(all/4+(all/2%2) + all %2,'\n');
            return;
        } 
        int rem = sum3;
        int k = min(sum1,sum3);
        tot += k;
        sum1 -= k,sum3 -= k;
        k = min(sum2*2,sum3);
        tot += k /2;
        sum2 -= k/2,sum3 -= k;
        print(sum1 + sum2 + rem,'\n');
        return;
    }
    void mian()
    {
        int T = read<int>();
        while(T--) solve();
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}