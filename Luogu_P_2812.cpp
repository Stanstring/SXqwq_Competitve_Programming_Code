#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
vector <int> Edge[N],newedge[N];
int n;
int dfn[N],low[N],in_stack[N];
int cnt,fa_cnt,fa[N],sum[N];
int in[N],out[N];
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
            int v = s.top();
            fa[v] = fa_cnt;
            sum[fa_cnt] ++;
            in_stack[v] = 0;
            s.pop();
        }
        s.pop();
        fa[u] = fa_cnt;
        sum[fa_cnt] ++;
        in_stack[u] = 0;
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
        int x;
        while(1)
        {
            cin>>x;
            if(!x) break;
            Edge[i].push_back(x);
        }
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
    {
        for(auto v:Edge[i])
        {
            if(fa[i] == fa[v]) continue;
            newedge[fa[i]].push_back(fa[v]);
            in[fa[v]] ++;
            out[fa[i]] ++;
        }
    }
    int ans1 = 0,ans2 = 0;
    for(int i=1;i<=fa_cnt;i++)
    {
        if(!in[i]) ans1 ++;
        if(!out[i] ) ans2 ++;
    } 
    if(fa_cnt == 1)
    {
        cout<<"1"<<endl<<"0"<<endl;
        exit(0);
    }
    ans2 = max(ans2,ans1);
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}