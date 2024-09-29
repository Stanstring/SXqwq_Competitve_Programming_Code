#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 5000100;
int n,q,m;
int a[N];
vector <int> Edge[N];
int tag[N];
int vis[N];
void dfs(int u,int fat,int tagnow)
{
    vis[u] = 1;
//    cout<<u<<"qvq"<<endl;
    a[u] += tagnow;
    for(auto v:Edge[u])
    {
        if(u == fat || vis[v]) continue;
        dfs(v,u,tagnow+tag[v]);
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    // puts("1");
    for(int i=1;i<n;i++) 
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
        
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op == 1) tag[x] += y;
        else 
        {
            a[x] += y;
            for(auto v:Edge[x]) a[v] += y;
        }
    }
    
    dfs(1,0,tag[1]);
    cin>>q;
    while(q--)
    {
        int x;
        cin>>x;
        cout<<a[x]<<endl;
    }
    return 0;
}