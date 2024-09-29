#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    typedef pair<int,int> PAIR;
    vector <PAIR> Edge[N];
    int L;
    struct PATH
    {
        int u,v,val;
        bool operator<(const PATH& a)const{
            return a.val < val;
        }
    };
    vector <PATH> path;
    int n,m;
    int a[N];
    int maxnpath = 0;
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N];
        void pushup(int p){tree[p] = tree[ls] + tree[rs];}
        void build(int l=1,int r=n,int p=1)
        {
            if(l == r) {tree[p] = a[l];return;}
            int mid = (l+r) >> 1;
            build(l,mid,ls);
            build(mid+1,r,rs);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return 0;
            if(l >= pl && r <= pr) return tree[p];
            int mid = (l+r) >> 1;
            return query(l,mid,pl,pr,ls) + query(mid+1,r,pl,pr,rs);
        }
    }seg;
    int dnf[N];
    int tot = 0;
    struct TCS
    {
        int L;
        #define x first
        #define y second
        int dfn[N],siz[N],tp[N],fa[N],depth[N],son[N],val[N];
        int cnt = 0;
        void dfs1(int u=1,int fat=0)
        {
            dnf[++tot] = u;
            depth[u] = depth[fat] + 1;
            siz[u] = 1;
            fa[u] = fat;
            int maxn = 0,maxx = 0;
            for(auto t:Edge[u])
            {
                int v = t.x,w = t.y;
                if(v == fat) continue;
                val[v] = w;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn) {maxn = siz[v];maxx = v;}
            }
            son[u] = maxx;
        }
        void dfs2(int u=1,int topp=0)
        {
            dfn[u] = ++cnt;
            a[cnt] = val[u];
            tp[u] = topp;
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto t:Edge[u])
            {
                int v = t.x;
                if(v == fa[u] || v == son[u]) continue;
                dfs2(v,v);
            }
        }
        PAIR query(int a,int b)
        {
            int sum = 0;
            while(tp[a] != tp[b])
            {
                if(depth[tp[a]] > depth[tp[b]]) swap(a,b);
                sum += seg.query(1,n,dfn[tp[b]],dfn[b],1);
                b = fa[tp[b]];
            }
            if(depth[a] > depth[b]) swap(a,b);
            sum += seg.query(1,n,dfn[a]+1,dfn[b],1);
            return PAIR(sum,a);
        }
    }tcs;
    struct BS
    {
        bool check(int k)
        {
            int res[N];
            int num = 0;
            fill(res+1,res+n+1,0);
            for(auto t:path)
            {
                int u = t.u,v = t.v,w = t.val;
                if(w <= k) continue;
                num ++;
                res[u] ++;
                res[v] ++;
                int LCA = tcs.query(u,v).second;
                res[LCA] -= 2;
            }
            for(int i=n;i>=1;i--)
            {
                res[tcs.fa[dnf[i]]] += res[dnf[i]];
                if(res[dnf[i]] == num && tcs.val[dnf[i]] >= maxnpath - k) return 1;
            }
            return 0;
        }
        void Binary_Search()
        {
            int l = maxnpath-L,r = maxnpath+1;
            while(l < r)
            {
            //    cerr<<l<<" "<<r<<endl;
                int mid = (l+r) >> 1;
                if(check(mid)) r = mid;
                else l = mid + 1;
            }
            cout<<l<<endl;
            return;
        }
    }bs;
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<n;i++) 
        {
            int u,v,w;
            cin>>u>>v>>w;
            Edge[u].push_back(PAIR(v,w));
            Edge[v].push_back(PAIR(u,w));
            L = max(L,w);
        }
        tcs.dfs1();
        tcs.dfs2();
        seg.build();
        for(int i=1;i<=m;i++)
        {
            int u,v;
            cin>>u>>v;
            int val = tcs.query(u,v).first;
            path.push_back({u,v,val});
            maxnpath = max(maxnpath,val);
        }
    //    cerr<<maxnpath<<endl;
        sort(path.begin(),path.end());
        bs.Binary_Search();   
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}