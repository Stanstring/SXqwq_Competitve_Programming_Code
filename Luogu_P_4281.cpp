#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    int n,m;
    vector <int> Edge[N];
    struct TCS
    {
        int dfn[N],siz[N],son[N],fa[N],tp[N],depth[N];
        int cnt = 0;
        void dfs1(int u,int fat)
        {
            fa[u] = fat;
            depth[u] = depth[fat] + 1;
            int maxn = 0,maxx = 0;
            siz[u] = 1;
            for(auto v:Edge[u])
            {
                if(v == fat) continue;
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
        void dfs2(int u,int topp)
        {
            tp[u] = topp;
            dfn[u] = ++cnt;
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto v:Edge[u])
            {
                if(v == son[u] || v == fa[u]) continue;
                dfs2(v,v);
            }
        }
        int get_lca(int u,int v)
        {
            while(tp[u] != tp[v])
            {
                if(depth[tp[u]] > depth[tp[v]]) swap(u,v);
                v = fa[tp[v]];
            }
            if(depth[u] > depth[v]) swap(u,v);
            return u;
        }
    }tcs;
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin>>u>>v;
            Edge[u].push_back(v),Edge[v].push_back(u);
        }
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        while(m--)
        {
            int x,y,z;
            cin>>x>>y>>z;
            int lca1 = tcs.get_lca(x,y),lca2 = tcs.get_lca(x,z),lca3 = tcs.get_lca(y,z);
            int min_lca = min({tcs.depth[lca1],tcs.depth[lca2],tcs.depth[lca3]});
            int max_lca = max({tcs.depth[lca1],tcs.depth[lca2],tcs.depth[lca3]});
            int ans = tcs.depth[x]+tcs.depth[y]+tcs.depth[z]-max_lca-(min_lca)*2;
            if(tcs.depth[lca1] == tcs.depth[lca2]) cout<<lca3<<" ";
            else if(tcs.depth[lca1] == tcs.depth[lca3]) cout<<lca2<<" ";
            else cout<<lca1<<" ";
            cout<<ans<<endl;
        }
        return;
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