#include <bits/stdc++.h>
using namespace std;
constexpr int N = 100010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    int n,m,cnt = 0;
    int dfn[N];
    int a[N];
    vector <int> Edge[N];
    void dfs(int u,int fa)
    {
        dfn[u] = ++cnt;
        for(auto v:Edge[u])
        {
            if(v == fa) continue;
            dfs(v,u);
        }
    }
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        struct TREE
        {
            int maxn,minn;
        }tree[N*8];
        void pushup(int p)
        {
            tree[p].maxn = max(tree[ls].maxn,tree[rs].maxn);
            tree[p].minn = min(tree[ls].minn,tree[rs].minn);
        }
        void build(int l,int r,int p)
        {
            if(l == r)
            {
                tree[p].maxn = tree[p].minn = a[l];
                return;
            }
            int mid = (l+r) >> 1;
            build(l,mid,ls);
            build(mid+1,r,rs);
            pushup(p);
        }
        int query_min(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return INF;
            if(l >= pl && r <= pr) return tree[p].minn;
            int mid = (l+r) >> 1;
            return min(query_min(l,mid,pl,pr,ls),query_min(mid+1,r,pl,pr,rs));
        }
        int query_max(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return -INF;
            if(l >= pl && r <= pr) return tree[p].maxn;
            int mid = (l+r) >> 1;
            return max(query_max(l,mid,pl,pr,ls),query_max(mid+1,r,pl,pr,rs));
        }
    }seg;
    struct LCA
    {
        int f[N][50];
        int depth[N];
        void dfs(int u,int fa)
        {
            f[u][0] = fa;
            depth[u] = depth[fa] + 1;
            for(int i=1;i<=30;i++) f[u][i] = f[f[u][i-1]][i-1];
            for(auto v:Edge[u])
            {
                if(v == fa) continue;
                dfs(v,u);
            }
        }
        int get_lca(int a,int b)
        {
            if(depth[a] > depth[b]) swap(a,b);
            for(int i=20;i>=0;i--)
            {
                if(depth[a] <= depth[b]-(1<<i)) b = f[b][i];
            }
            if(a == b) return a;
            for(int i=20;i>=0;i--)
            {
                if(f[a][i] == f[b][i]) continue;
                a = f[a][i];
                b = f[b][i];
            }
            return f[a][0];
        }
    }lca;
    struct TCS
    {
        int cnt = 0;
        int fa[N];
        int dfn[N],siz[N],son[N],depth[N],tp[N];
        void dfs1(int u,int fat)
        {
            depth[u] = depth[fat] + 1;
            siz[u] = 1;
            fa[u] = fat;
            int maxn = 0,maxx = 0;
            for(auto v:Edge[u])
            {
                if(v == fat) continue;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn){maxn = siz[v];son[u] = v;}
            }
        }
        void dfs2(int u,int topp)
        {
            tp[u] = topp;
            dfn[u] = ++cnt;
            a[cnt] = u;
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto v:Edge[u]) 
            {
                if(v == son[u] || v == fa[u]) continue;
                dfs2(v,v);
            }
        }
        int query(int x,int y)
        {
            int ans = 1;
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                ans = max(ans,seg.query_max(1,n,dfn[tp[y]],dfn[y],1));
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            ans = max(ans,seg.query_max(1,n,dfn[x],dfn[y],1));
            return ans;
        }
    }tcs;
    void solve()
    {
        cin>>n;
        for(int i=2;i<=n;i++) 
        {
            int t;
            cin>>t;
            t ++;
            Edge[t].push_back(i);
            Edge[i].push_back(t);
        } 
        dfs(1,0);
        lca.dfs(1,0);
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        seg.build(1,n,1);
        int q;
        cin>>q;
        while(q--)
        {
            int m;
            cin>>m;
            int maxn = 0,minn = INF,maxx=0,minx=0;
            for(int i=1;i<=m;i++) 
            {
                int t;
                cin>>t;
                t ++;
                if(dfn[t] > maxn){maxn = dfn[t];maxx = t;}
                if(dfn[t] < minn){minn = dfn[t];minx = t;}
            }
            int LCA = lca.get_lca(maxx,minx);
            int ans= tcs.query(1,LCA);
            cout<<ans-1<<endl;
        }
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