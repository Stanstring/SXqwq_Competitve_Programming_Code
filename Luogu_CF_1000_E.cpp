#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 500010;
constexpr int INF = 0x3f3f3f3f;
int n,m;
vector <int> Edge[N];
int dfn[N],low[N];
stack <int> s;
int cnt = 0;
int fat[N];
int fa_cnt = 0;
int tmp1,tmp2;
int d[N],d1[N],d2[N];
vector <int> edgenew[N];
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
void dfs(int now,int fa,int dis)
{
    for(int i=0;i<edgenew[now].size();i++)
    {
        int v = edgenew[now][i],u = now;
        if(v == fa) continue;
        dfs(v,now,dis+1);
     }
     int u = now;
     d[u] = dis;
    if(dis > tmp2)
    {
        tmp2 = dis;
        tmp1 = u;
    }
}
void bfs(int st,int ed)
{
    queue <int> q;
    int vis[N];
    fill(vis+1,vis+fa_cnt+1,INF);
    q.push(st);
    vis[st] = 0;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        if(p == ed)
        {
            cout<<vis[ed]<<endl;
            exit(0);
        }
        for(auto v:edgenew[p])
        {
            if(vis[v] != INF) continue;
            vis[v] = vis[p] + 1;
            q.push(v);
        }
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
    tarjan(1,0);
    for(int i=1;i<=n;i++)
    {
        for(auto v:Edge[i])
        {
            if(fat[i] != fat[v]) edgenew[fat[i]].push_back(fat[v]);
        }
    }
    dfs(1,0,0);
    int pos1 = tmp1;
    tmp2 = 0,tmp1 = 0;
    dfs(pos1,0,0);
    int pos2 = tmp1;
    tmp2 = 0,tmp1 = 0;
    for(int i=1;i<=fa_cnt;i++) d1[i] = d[i];
    dfs(pos2,0,0);
    bfs(pos1,pos2);
}