#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
int n,m;
vector <int> Edge[N];
int dfn[N],low[N];
int d[N];
int cnt = 0;
int b[N];
stack <int> s;
int tot = 0;
vector <int> ans[N];
void tarjan(int u,int fa)
{
    dfn[u] = low[u] = ++tot;
    s.push(u);
    if(!d[u])
    {
        ans[++cnt].push_back(u);
    }
    for(auto v:Edge[u])
    {
        if(!dfn[v]) 
        {
            tarjan(v,u);
            low[u] = min(low[u],dfn[v]);
            if(dfn[u] <= low[v]) 
            {
                ++cnt;
                int t;
                do
                {
                    t = s.top();
                    ans[cnt].push_back(t);
                    s.pop();
                }while(t != v);
                ans[cnt].push_back(u);
            }
            low[u] = min(low[u],low[v]); 
        }
        else low[u] = min(low[u],dfn[v]);
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
        if(u == v) continue;
        d[u] ++;
        d[v] ++;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++) 
    {
        if(!dfn[i]) tarjan(i,i);
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)
    {
        cout<<ans[i].size()<<" ";
        for(auto v:ans[i])
        {
            cout<<v<<" ";
        }
        cout<<endl;
    }
}