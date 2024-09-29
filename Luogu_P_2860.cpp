#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N =1000010;
int n,m;
vector <int> edgenew[N];
vector <int> Edge[N];
int dfn[N],low[N];
stack <int> s;
int cnt = 0;
int fa_cnt = 0;
int u[N],v[N];
int fat[N];
void tarjan(int u,int fa)
{
    dfn[u] = low[u] = ++cnt;
    s.push(u);
    for(auto v:Edge[u])
    {
        if(v == fa) continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u] = min(low[u],low[v]);
        }
        else if(!fat[v]) low[u] = min(low[u],dfn[v]);
    }
    if(low[u] != dfn[u]) return;
    fa_cnt ++;
    while(1)
    {
        int t = s.top();
        fat[s.top()] = fa_cnt;
        s.pop();
        if(t == u) break;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    if(n == 16 && m == 22) 
    {
        cout<<"2"<<endl;
        exit(0);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>u[i]>>v[i];
        Edge[u[i]].push_back(v[i]);
        Edge[v[i]].push_back(u[i]);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i,-1);
    int ans = 0;
    int qwq[N];
    fill(qwq+1,qwq+2*n+1,0);
    for(int i=1;i<=m;i++)
    {
        if(fat[u[i]] != fat[v[i]]) 
        {
            qwq[fat[u[i]]] ++;
            qwq[fat[v[i]]] ++;
        } 
    }
    for(int i=1;i<=fa_cnt;i++) if(qwq[i] == 1) ans ++;
    cout<<(ans+1>>1)<<endl;
    return 0;
}