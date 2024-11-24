#include <bits/stdc++.h>
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
    int a[N],b[N];
    void solve()
    {
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) {if(a[j] > a[i]) b[j] = 1;else if(a[j] < a[i]) b[j] = -1;else b[j] = 0;}
            for(int j=1;j<=n;j++) b[j] += b[j-1];
            bool flag = 0;
            for(int l=i;l>=1;l--)
            {
                for(int r=i;r<=n;r++){ if(b[r] - b[l-1] == 0 && l != r && (r-l+1) % 2 != 0){flag = 1;break;}}
                if(flag) break;
            }
            if(flag) cout<<"y";
            else cout<<"n";
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}