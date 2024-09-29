#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t int
using namespace std;
using namespace __gnu_pbds;
const int N = 1000010;
size_t n;
size_t val[N];
vector <int> Edge[N];
size_t f[N],g[N];
void dfs1(int u,int fat)
{
    f[u] = val[u];
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        dfs1(v,u);
        f[u] += max(f[v],0);
    }
}
void dfs2(int u,int fat)
{
    g[u] = f[u];
    g[u] += max(0,g[fat]-max(f[u],0));
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        dfs2(v,u);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        size_t t;
        cin>>t;
        if(!t) val[i] = -1;
        else val[i] = 1;
    }
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout<<g[i]<<" ";
    cout<<endl;
    return 0;
}