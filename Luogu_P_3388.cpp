#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long 
using namespace std;
constexpr int N = 1000010;
int n,m;
vector <int> Edge[N];
int dfn[N],low[N];
int cnt = 0;
int ans[N];
int countt = 0;
void tarjan(int pos,int root)
{
    int childnum = 0;
    dfn[pos] = low[pos] = ++cnt;
    for(auto v:Edge[pos])
    {
        if(!dfn[v])
        {
            tarjan(v,root);
            low[pos] = min(low[pos],low[v]);
            if(low[v] >= dfn[pos]) ++childnum;
        }
        else low[pos] = min(low[pos],dfn[v]);
    }
    if(pos == root && childnum > 1) 
    {
        countt ++;
        ans[pos] = 1;
        return;
    }
    else if(pos != root && childnum > 0)
    {
        countt ++;
        ans[pos] = 1;
        return;
    }
}   
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++) tarjan(i,i);
    cout<<countt<<endl;
    for(int i=1;i<=n;i++)
        if(ans[i]) cout<<i<<" ";
    return 0;
}