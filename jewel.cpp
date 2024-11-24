#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 2e5 + 10;
constexpr int null = -1;
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
    #define x first
    #define y second
    typedef pair<int,int> PII;
    struct Node
    {
        int l,r,num;
        bool operator<(const Node& t)const{
            return r < t.r;
        }
    };
    int n,q;
    int a[N],b[N],last[N];
    int ans[N];
    vector <Node> ask;
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N*4];
        void pushup(int p){tree[p] = min(tree[ls],tree[rs]);}
        void build(int l = 1,int r = n,int p = 1)
        {
            if(l == r){tree[p] = INF;return;}
            int mid = (l+r) >> 1;
            build(l,mid,ls),build(mid+1,r,rs);
            pushup(p);
        }
        void modify(int l,int r,int pos,int p,int d)
        {
            if(l == r) {tree[p] = min(tree[p],d);return;}
            int mid = (l+r) >> 1;
            if(pos <= mid) modify(l,mid,pos,ls,d);
            else modify(mid+1,r,pos,rs,d);
            pushup(p); 
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l >= pl && r <= pr) return tree[p];
            int mid = (l+r) >> 1,minn = INF;
            if(pl <= mid) minn = min(minn,query(l,mid,pl,pr,ls));
            if(pr > mid) minn = min(minn,query(mid+1,r,pl,pr,rs));
            return minn;
        }
    }seg;
    void solve()
    {
        n = read<int>(),q = read<int>();
        seg.build();
        for(int i=1;i<=n;i++) {a[i] = read<int>();b[i] = a[i];}
        sort(a+1,a+n+1);
        int t = unique(a+1,a+n+1)-a-1;
        for(int i=1;i<=n;i++) b[i] = lower_bound(a+1,a+n+1,b[i]) - a;
        for(int i=1;i<=q;i++) {int l,r;l = read<int>(),r = read<int>();ask.push_back({l,r,i});}
        sort(ask.begin(),ask.end());
        int pos = 0;
        for(auto [l,r,num]:ask)
        {
            while(pos <= r){if(last[b[pos]]) seg.modify(1,n,last[b[pos]],1,pos - last[b[pos]]);last[b[pos]] = pos;pos ++;}
            ans[num] = seg.query(1,n,l,r,1);
        }
        for(int i=1;i<=q;i++) print(ans[i]!=INF?ans[i]:null,'\n');
        return;
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