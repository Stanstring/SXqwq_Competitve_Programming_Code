#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 2e5 + 10;
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
    typedef pair<int,int> PII;
    vector <PII> Edge[N];
    int n,q;
    int f1[N],f[N],c[N];
    int a[N],dis[N];
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N*4];
        void pushup(int p){tree[p] = max(tree[ls],tree[rs]);}
        void build(int l = 1,int r = n,int p = 1)
        {
            if(l == r){tree[p] = a[l];return;}
            int mid = (l+r) >> 1;
            build(l,mid,ls);build(mid+1,r,rs);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l >= pl && r <= pr) return tree[p];
            int maxn = 0;
            int mid = (l+r) >> 1;
            if(pl <= mid) maxn = max(maxn,query(l,mid,pl,pr,ls));
            if(pr > mid) maxn = max(maxn,query(mid+1,r,pl,pr,rs));
            return maxn;
        }
    }seg;
    struct TCS
    {
        int tot = 0;
        int dfn[N],siz[N],depth[N],son[N],fa[N],tp[N];
        void dfs1(int u,int fat)
        {
            fa[u] = fat;
            depth[u] = depth[fat] + 1;
            siz[u] = 1;
            int maxn = 0,maxx = 0;
            for(auto [v,w]:Edge[u])
            {
                if(v == fat) continue;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn){maxn = siz[v];maxx = v;}
            }
            son[u] = maxx;
        }
        void dfs2(int u,int topp)
        {
            tp[u] = topp;
            dfn[u] = ++tot;
            a[tot] = f[u];
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto [v,w]:Edge[u]){if(v == fa[u] || v == son[u]) continue;dfs2(v,v);}
        }
        PII query(int x,int y)
        {
            int maxn = 0;
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                maxn = max(maxn,seg.query(1,n,dfn[tp[y]],dfn[y],1));
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            maxn = max(maxn,seg.query(1,n,dfn[x],dfn[y],1));
            return PII(maxn,x);
        }
    }tcs;
    struct INIT
    {
        void dfs1(int u,int fat,int sum)
        {
            dis[u] = sum;
            f1[u] = c[u];
            for(auto [v,w]:Edge[u])
            {
                if(v == fat) continue;
                dfs1(v,u,sum + w);
                f1[u] = max(f1[u],f1[v] - 2*w);
            }
        }
        void dfs2(int u,int fat)
        {
            for(auto [v,w]:Edge[u])
            {
                if(v == fat) continue;
                f[v] = max({c[v],f1[u]-2*w,f[u]-2*w});
                dfs2(v,u);
            }
        }
    }init;
    void solve()
    {
        n = read<int>(),q = read<int>();
        for(int i=1;i<=n;i++) c[i] = read<int>();
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            u = read<int>(),v = read<int>(),w = read<int>();
            Edge[u].push_back(PII(v,w));Edge[v].push_back(PII(u,w));
        }
        init.dfs1(1,0,0),init.dfs2(1,0);
        for(int i=1;i<=n;i++) f[i] = max(f[i],f1[i]);
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        seg.build();
        while(q--)
        {
            int x,y;
            x = read<int>(),y = read<int>();
            auto t = tcs.query(x,y);
            int LCA = t.second;
            int dist = dis[x] + dis[y] - 2*dis[LCA];
            print(c[x] + c[y] - dist + t.first,'\n');
        }
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