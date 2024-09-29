#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100010;
const int mod = 998244353;
vector <int> Edge[N];
int n;
int f[N],ans[N];
vector <int> f1[N],f2[N];
void dfs1(int u,int fat)
{
    f[u] = 1;
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        dfs1(v,u);
        f[u] = f[u]*(f[v]+1)%mod;
    }
}
void dfs2(int u,int fat)
{
    ans[u] = 1;
    for(auto v:Edge[u])
    {
        ans[u] = ans[u]*(f[v]+1)%mod;
        if(v == fat) continue;
        f1[u].push_back(f[v]+1);
        f2[u].push_back(f[v]+1);
    }
    for(int i=1;i<f1[u].size();i++)
        f1[u][i] = f1[u][i]*f1[u][i-1]%mod;
    for(int i=f2[u].size()-2;i>=0;i--) 
        f2[u][i] = f2[u][i]*f2[u][i+1]%mod;
    int cnt = 0;
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        if(!fat) f[u] = 1;
        else f[u] = f[fat] + 1;
        if(cnt > 0) f[u] = f[u]*f1[u][cnt-1]%mod;
        if(cnt < f2[u].size()-1) f[u] = f[u]*f2[u][cnt+1]%mod;
        dfs2(v,u);
        cnt ++;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        int t;
        cin>>t;
        Edge[t].push_back(i);
        Edge[i].push_back(t);
   }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}