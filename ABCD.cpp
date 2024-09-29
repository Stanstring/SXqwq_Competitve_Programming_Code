#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    #define x first
    #define y second
    typedef pair<int,int> PII;
    vector <PII> Edge[N];
    vector <PII> Edge1[N];
    int ans[N];
    int vis[N];
    int n,m;
    int in[N];
    queue <int> q;
    void dfs(int u)
    {
        for(auto t:Edge[u])
        {
            int v = t.x,w = t.y;
            if(!vis[v]) 
            {
                vis[v] = 1;
                ans[v] = ans[u] + w;
                dfs(v);
            }
        }
        for(auto t:Edge1[u])
        {
            int v = t.x,w = t.y;
            if(!vis[v])
            {
                vis[v] = 1;
                ans[v] = ans[u] - w;
                dfs(v);
            }
        }
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++) 
        {
            int u,v,w;
            cin>>u>>v>>w;
            Edge[u].push_back(PII(v,w));
            Edge1[v].push_back(PII(u,w));
            in[v] ++;
        }
        int res = 1e9;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]) 
            {
                vis[i] = 1;
                ans[i] = 0;
                dfs(i);
            }
        }
        for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
        cout<<endl;
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