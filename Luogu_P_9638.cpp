#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    typedef pair<int,int> PAIR;
    int n,m,q,limi;
    int tot;
    struct Node
    {
        int u,v,w,id;
        bool operator <(const Node& a)const{
            return a.w < w;
        }
    };
    vector <Node> edge;
    vector <PAIR> Edge[N];
    int edge_num[N],fa[N][50],siz[N];
    int val[N];
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=n*2+1;i++) fa[i] = i;}
        int find(int x)
        {
            if(x == fa[x]) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        } 
        void merge(int x,int y)
        {
            int i = find(x),j = find(y);
            if(i == j) return;
            fa[i] = j;
        }
    }dsu;
    void kruskal()
    {
        sort(edge.begin(),edge.end());
        tot = n; 
        dsu.init();
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),w = t.w;
            if(u == v) continue;
            tot ++;
            dsu.merge(u,tot),dsu.merge(v,tot);
            Edge[tot].push_back(PAIR(u,w)),Edge[tot].push_back(PAIR(v,w));
            edge_num[t.id] = tot;
            val[tot] = w;
        }
    }
    void dfs(int u,int fat)
    {
        #define x first
        #define y second
        for(int i=1;i<=30;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        if(u <= n) 
        {
            siz[u] = 1;
            return;
        }
        for(auto t:Edge[u])
        {
            int v = t.x;
            if(siz[t.x] || t.x == fat) continue;
            fa[t.x][0] = u;
            dfs(t.x,u);
            siz[u] += siz[v];
        }
    }
    int find_max(int u)
    {
        for(int i=30;i>=0;i--)
            if(fa[u][i] && val[fa[u][i]] >= limi) u = fa[u][i];
        return u;
    }
    void solve()
    {
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            edge.push_back({u,v,w,i});
        }
        kruskal();
       // cerr<<tot<<endl;
        for(int i=tot;i;i--) if(!siz[i]) dfs(i,0);
        while(q--)
        {
            int op;
            cin>>op;
            if(op == 1) 
                cin>>limi;
            else if(op == 2)
            {
                int x;
                cin>>x;
                cout<<siz[find_max(x)]<<endl;
            }
            else if(op == 3)
            {
                int x,y;
                cin>>x>>y;
                val[edge_num[x]] = y;
            }
        }
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}