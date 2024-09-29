#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
typedef pair<int,int> PAIR;
struct Node
{
    int u,v,w;
};
int n,m;
vector <int> Edge[N];
vector <Node> qwq;
PAIR path[N];
int dfn[N],siz[N],tp[N],son[N],depth[N],fat[N];
int cnt = 0;
int tree[N],mark[N];
void dfs1(int u,int f)
{
    fat[u] = f;
    depth[u] = depth[f] + 1;
    siz[u] = 1;
    int maxn = 0,maxx = 0;
    for(auto v:Edge[u])
    {
        if(v == f) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v] > maxn)
        {
            maxn = siz[v];
            maxx = v;
        }
    }
    son[u] = maxx;
}
void dfs2(int u,int topp)
{
    dfn[u] = ++cnt;
    tp[u] = topp;
    if(!son[u]) return;
    dfs2(son[u],topp);
    for(auto v:Edge[u])
    {
        if(v == fat[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
void pushdown(int p,int len)
{
    tree[p<<1] = min(tree[p<<1],mark[p]);
    tree[p<<1|1] = min(tree[p<<1|1],mark[p]);
    mark[p<<1] = min(mark[p<<1],mark[p]);
    mark[p<<1|1] = min(mark[p<<1|1],mark[p]);
    mark[p] = INF;
}
void modify(int l,int r,int pl,int pr,int p,int d)
{
    if(l > pr || r < pl) return;
    if(l >= pl && r <= pr)
    {
        tree[p] = min(tree[p],d);
        mark[p] = min(mark[p],d);
        return;
    }
    int mid = (l+r) >> 1;
    pushdown(p,r-l+1);
    modify(l,mid,pl,pr,p<<1,d);
    modify(mid+1,r,pl,pr,p<<1|1,d);
    tree[p] = min(tree[p<<1],tree[p<<1|1]);
}
void update_path(int x,int y,int d)
{
    while(tp[x] != tp[y])
    {
        if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
        modify(1,n,dfn[tp[y]],dfn[y],1,d);
        y = fat[tp[y]];
    }
    if(depth[x] > depth[y]) swap(x,y);
    modify(1,n,dfn[x]+1,dfn[y],1,d);
}
int query(int l,int r,int pos,int p)
{
    if(l == r) return tree[p];
    pushdown(p,r-l+1);
    int mid = (l+r) >> 1;
    if(mid >= pos) return query(l,mid,pos,p<<1);
    if(mid+1 <= pos) return query(mid+1,r,pos,p<<1|1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
        path[i] = PAIR(u,v);

    }
    dfs1(1,0);
    dfs2(1,0);
    memset(tree,INF,sizeof(tree));
    memset(mark,INF,sizeof(mark));
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        update_path(u,v,w);
    }
    for(int i=1;i<n;i++)
    {
        int u = path[i].first,v = path[i].second;
        if(fat[u] == v) swap(u,v);
        int ans = query(1,n,dfn[v],1);
        if(ans >= INF) cout<<"-1"<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}