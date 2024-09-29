#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
int n,m;
vector <int> Edge[N];
int dfn[N],low[N];
int cnt = 0;
int b[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    for(auto v:Edge[u])
    {
        if(!dfn[v]) 
        {
            tarjan(v);
            if(dfn[u] < low[v]) b[i] = b[i^1] = 1;
            low[u] = min(low[u],low[v]); 
        }
        else if(i != ())
    }
}
int main()
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
}