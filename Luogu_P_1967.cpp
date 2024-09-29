#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    typedef pair<int,int> PAIR;
    vector <int> Edge[N];
    int f[N][40];
    int val[N];
    int n,m;
    int tot;
    struct Node
    {
        int u,v,w;
        bool operator<(const Node& a)const{
            return a.w < w;
        }
    };
    vector <Node> edge;
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=n*2;i++) fa[i] = i;}
        int find(int x)
        {
            if(fa[x] == x) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        }
        void merge(int x,int y)
        {
            int i = find(x),j = find(y);
            fa[j] = i;
        }
    }dsu;
    struct TCS
    {
        int dfn[N],fa[N],siz[N],son[N],depth[N],tp[N];
        int cnt = 0;
        void dfs1(int u,int f )
        {
            depth[u] = depth[f] + 1;
            siz[u] = 1;
            fa[u] = f;
            int maxn = 0,maxx = 0;
            for(auto v:Edge[u])
            {
                if(v == f) continue;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn)
                {
                    maxn = siz[v];
                    maxx = v;
                }
            }
            son[u] = maxx;
        }
        void dfs2(int u,int fat)
        {
            f[u][0] = fat;
            for(int i=1;i<=30;i++) f[u][i] = f[f[u][i-1]][i-1];
            for(auto v:Edge[u])
            {
                if(v == fat) continue;
                dfs2(v,u);
            }
        }
        int get_lca(int x,int y)
        {
            if(depth[x] > depth[y]) swap(x,y);
            for(int i=30;i>=0;i--)
            {
                if(f[y][i] && depth[f[y][i]] > depth[x]) y = f[y][i];
            }
            if(depth[x] != depth[y]) y = f[y][0];
            for(int i=30;i>=0;i--)
            {
                if(f[x][i] && f[y][i] && f[x][i] != f[y][i]) 
                {
                    x = f[x][i];
                    y = f[y][i];
                }
            }
            return f[x][0];
        }
    }tcs;
    void kruskal()
    {
        sort(edge.begin(),edge.end());
        dsu.init();
        tot = n;
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),w = t.w;
            if(u == v) continue;
            tot ++;
            dsu.merge(tot,u);
            dsu.merge(tot,v);
            Edge[tot].push_back(u);
            Edge[tot].push_back(v);
            val[tot] = w;
        }
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            edge.push_back({u,v,w});
        }
        kruskal();
        for(int i=tot;i>=1;i--)
        {
            if(!tcs.siz[i]){tcs.dfs1(i,0);tcs.dfs2(i,0);}
        }
        int q;
        cin>>q;
        while(q--)
        {
            int x,y;
            cin>>x>>y;
            int LCA = tcs.get_lca(x,y);
            cout<<((!val[LCA])?-1:val[LCA])<<endl;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}