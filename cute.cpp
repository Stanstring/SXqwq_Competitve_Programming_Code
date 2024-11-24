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
    int a[N],num[N],sum[N];
    void solve()
    {
        n = read<int>();
        int tot = 0,all = 0;
        for(int i=1;i<=n;i++) {a[i] = read<int>();sum[i] = sum[i-1] + a[i];all += sum[i];}
        for(int i=1;i<n;i++) {if(a[i] < a[i+1]){tot += a[i+1] - a[i];a[i+1] = a[i];}} 
        int pos = 1,lst = n;
        int kill = 0;
        for(int i=n;i>=1;i--)
            while(a[i] >= pos){num[pos] = i;pos ++;}
        for(int i=1;i<=n;i++)
        {
            if(a[i] > num[i]) {tot += (a[i] - num[i]);kill += (a[i]-num[i]);a[i] = num[i];}
            else if(num[i] > a[i]) {int minus = num[i] - a[i];lst = min(lst,num[i]);tot += (sum[lst] - sum[lst-minus])-kill-(i-1);lst -= minus;}
            if(a[i] == num[i] && (a[i] == i || a[i] == i-1)) {break;}
        }
        print(tot,'\n');
    }
    void mian()
    {
        int T = read<int>();
        while(T--) solve();
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}