#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
struct Node
{
    int id,v,w;
};
vector <int> Edge[N];
vector <Node> query[N];
int n,m,k;
int ans[N];
int dis[N][10];
int inq[N];
void spfa(int st)
{
    for(int i=1;i<=n;i++) dis[i][0] = dis[i][1] = INF;
    fill(inq+1,inq+1+n,0);
    queue <int> q;
    q.push(st);
    inq[st] = 1;
    dis[st][0] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for(auto v:Edge[u])
        {
            if(dis[u][0] + 1 < dis[v][1])
            {
                dis[v][1] = dis[u][0] + 1;
                if(!inq[v]){ inq[v] = 1;q.push(v);}
            }
            if(dis[u][1] + 1 < dis[v][0])
            {
                dis[v][0] = dis[u][1] + 1;
                if(!inq[v]) {inq[v] = 1;q.push(v);}
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    for(int i=1;i<=k;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        query[u].push_back({i,v,w});
    }
    for(int u=1;u<=n;u++)
    {
        if(!query[u].empty() && Edge[u].size())
        {
            spfa(u);
            for(auto t:query[u]) ans[t.id] = (t.w >= dis[t.v][t.w&1]); 
        }
    }
    for(int i=1;i<=k;i++)
    {
        if(ans[i]) cout<<"TAK"<<endl;
        else cout<<"NIE"<<endl;
    }
    return 0;
}
