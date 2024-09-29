#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    typedef pair<int,int> PAIR;
    vector <int> Edge[N];
    vector <PAIR> edge;
    int ans[N];
    int n,m,cnt = 0;
    int vis[N];
    void dfs(int u,int fa)
    {
        if(vis[u]) return;
        vis[u] = 1;
        ans[++cnt] = u;
        for(auto v:Edge[u])
        {
            if(v == fa) continue;
            dfs(v,u);
        }
    }
    struct BRT
    {
        #define x first
        #define y second
        int banu = 0,banv = 0;
        int ans[N],res[N],vis[N],cnt = 0;
        void dfs1(int u,int f)
        {
            if(vis[u]) return;
            vis[u] = 1;
            res[++cnt] = u;
            for(auto v:Edge[u])
            {
                if((banu == u && banv == v) || (banu == v && banv == u)) 
                {
                    continue;
                }
                if(v == f) continue;
                dfs1(v,u);
            }
        }
        bool Change_Check()
        {
            if(cnt < n) return 0;
            if(!ans[1]) return 1;
            for(int i=1;i<=n;i++) 
            {
                if(res[i] < ans[i]) return 1;
                if(res[i] > ans[i]) return 0;
            }
                
            return 0;
        }
        void modify(){for(int i=1;i<=n;i++) ans[i] = res[i];}
        void mian()
        {
            for(auto t:edge)
            {
                banu = t.x,banv = t.y;
                fill(res+1,res+n+1,0);
                fill(vis+1,vis+n+1,0);
                cnt = 0;
                dfs1(1,0);
                if(Change_Check()) modify();
            }
            for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
            cout<<endl;
            exit(0);
        }
    }brt;
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++)
        {
            int u,v;
            cin>>u>>v;
            Edge[u].push_back(v);
            Edge[v].push_back(u);
            edge.push_back(PAIR(u,v));
        }
        for(int i=1;i<=n;i++) sort(Edge[i].begin(),Edge[i].end());
        if(n == m) brt.mian();
        dfs(1,0);
        for(int i=1;i<=cnt;i++) cout<<ans[i]<<" ";
        cout<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}