#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
namespace solution

    int n,m,s;
    vector <int> Edge[N];
    struct LCA
    {
        int fa[N][40];
        int depth[N];
        void dfs(int u,int fat)
        {
            depth[u] = depth[fat] + 1;
            fa[u][0] = fat;
            for(int i=1;i<=30;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
            for(auto v:Edge[u]) 
            {
                if(v == fat) continue;
                dfs(v,u);
            }
        }
        int get_lca(int x,int y)
        {
            if(depth[x] > depth[y]) swap(x,y);
            for(int i=30;i>=0;i--) if(depth[fa[y][i]] > depth[x]) y = fa[y][i];
            if(depth[x] != depth[y] )y = fa[y][0];
            if(x == y) return x;
            for(int i=30;i>=0;i--) 
                if(fa[x][i] != fa[y][i]) {x = fa[x][i];y = fa[y][i];}
            return fa[x][0];
        }
    }lca;
    void solve()
    {
        cin>>n>>m>>s;
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin>>u>>v;
            Edge[u].push_back(v);
            Edge[v].push_back(u);
        }
        lca.dfs(s,0);
        for(int i=1;i<=m;i++)
        {
            int a,b;
            cin>>a>>b;
            cout<<lca.get_lca(a,b)<<endl;
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