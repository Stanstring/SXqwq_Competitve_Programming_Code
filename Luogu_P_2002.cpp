#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
int n,m;
vector <int> Edge[N],newedge[N];
int in[N];
int sum[N];
int dfn[N],low[N],fa[N];
int fa_cnt,cnt;
int in_stack[N];
stack <int> s;
void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    in_stack[u] = 1;
    s.push(u);
    for(auto v:Edge[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(in_stack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        fa_cnt ++;
        while(s.top() != u)
        {
            sum[fa_cnt] ++;
            fa[s.top()] = fa_cnt;
            in_stack[s.top()] = 0;
            s.pop();
        }   
        s.pop();
        sum[fa_cnt] ++;
        fa[u] = fa_cnt;
        in_stack[u] = 0;
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
    } 
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
    {
        for(auto v:Edge[i])
        {
            if(fa[v] == fa[i]) continue;
            bool can_push = 1;
            for(auto t:newedge[fa[i]])
                if(t == fa[v]) {can_push = 0;break;}
            if(!can_push) continue;
            newedge[fa[i]].push_back(fa[v]);
            in[fa[v]] ++;
        }
    }
    int ans = 0;
    for(int i=1;i<=fa_cnt;i++) if(!in[i]) ans ++;
    cout<<ans<<endl;
    return 0;
}