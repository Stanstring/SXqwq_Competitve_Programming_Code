#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    typedef pair<int,int> PAIR;
    struct Node
    {
        int u,v,a;
        bool operator< (const Node& t)const{
            return t.a < a;
        }
    };
    vector <Node> edge;
    vector <PAIR> Edge[N];
    vector <int> et[N];
    int val[N];
    int dis[N],vis[N];
    int fa[N][50];
    int n,m;
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=2*n;i++) fa[i] = i;}
        int find(int x)
        {
            if(x == fa[x]) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        }
        bool merge(int x,int y)
        {
            int i = find(x),j = find(y);
            if(i == j) return 0;
            fa[i] = j;
            return 1;
        }
    }dsu;
    void dfs(int u,int fat)
    {
        fa[u][0] = fat;
        for(int i=1;i<=19;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        for(auto v:et[u])
        {
            dfs(v,u);
            dis[u] = min(dis[u],dis[v]);
        }
    }
    void dijkstra(int s)
    {
        #define x first
        #define y second
        memset(dis,INF,sizeof(dis));
        memset(vis,0,sizeof(vis));
        priority_queue <PAIR> q;
        dis[s] = 0;
        q.push(PAIR(0,s));
        while(!q.empty())
        {
            PAIR p = q.top();
            int u = p.y;
            q.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(auto t:Edge[u])
            {
                int v = t.x,l = t.y;
                if(dis[v] > dis[u] + l)
                {
                    dis[v] = dis[u] + l;
                    q.push(PAIR(-dis[v],v));
                }
            }
        }
    }
    void kruskal()
    {
        dsu.init();
        sort(edge.begin(),edge.end());
        int noww = n;
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),a = t.a;
            if(u == v) continue;
            val[++noww] = a;
            dsu.merge(u,noww);
            dsu.merge(v,noww);
            et[noww].push_back(u);
            et[noww].push_back(v);
        }
    }
    void memset0()
    {
        memset(val,0,sizeof(val));
        memset(fa,0,sizeof(fa));
        for(int i=1;i<=n;i++) Edge[i].clear();
        for(int i=1;i<=2*n;i++) et[i].clear();
        edge.clear();
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++) 
        {
            int u,v,l,a;
            cin>>u>>v>>l>>a;
            edge.push_back({u,v,a});
            Edge[u].push_back(PAIR(v,l));
            Edge[v].push_back(PAIR(u,l));
        }
        dijkstra(1);
        kruskal();
        dfs(2*n-1,0);
        int q,k,s;
        cin>>q>>k>>s;
        int lst = 0;
        while(q--)
        {
            int v,p;
            cin>>v>>p;
            v = (v+k*lst-1)%n+1;
            p = (p+k*lst)%(s+1);
            for(int i = 19;i>=0;i--)
            {
                if(val[fa[v][i]] > p) v = fa[v][i];
            }
            cout<<dis[v]<<endl;
            lst = dis[v];
        }
        memset0();
    }
    void main()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::main();
}