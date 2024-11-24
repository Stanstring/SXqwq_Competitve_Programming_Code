#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int INF = 0x3f3f3f3f;
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
    int n,a,b;
    string s;
    int cnt0 = 0,cnt1 = 0;
    void solve()
    {
        int minn = INF;
        cnt1 = cnt0 = 0;
        cin>>n>>a>>b;
        cin>>s;
        for(int i=0;i<s.size();i++) {if(s[i] == '0') cnt0 ++;else cnt1 ++;}
        if(!a || !b) {cout<<"0\n";return;}
        minn = min({minn,a*cnt0,b*cnt0});
        minn = min({minn,a*cnt1,cnt1/2*b+a*(cnt1%2)});
        cout<<minn<<"\n";
        return;
    }
    void mian()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
signed main()
{
    // freopen("ringtu.in","r",stdin);
    // freopen("ringtu.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}