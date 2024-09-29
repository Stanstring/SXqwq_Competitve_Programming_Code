#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 5000010;
struct Node
{
    int a,b,c;
}Edge[N],d[N];
struct TREE
{
    int l,r,maxx;
}tree[N];
int n,m;
int fa[N];
int MST = 0;
int rev[N];
int tot = 1;
vector <int> g[N],e[N];
int a[N];
int top[N];
int depth[N],fat[N],dfn[N],siz[N],son[N];
int cnt_tree = 0;
int seg[N];
void init(){for(int i=1;i<=n;i++) fa[i] = i;}
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
bool cmp(Node a,Node b){return a.c < b.c;}
void kruskal()
{
    for(int i=1;i<=m;i++)
    {
        int ii = find(Edge[i].a),jj = find(Edge[i].b);
        if(ii == jj) continue;
        fa[ii] = jj;
        g[Edge[i].a].push_back(Edge[i].b);
        g[Edge[i].b].push_back(Edge[i].a);
        e[Edge[i].a].push_back(Edge[i].c);
        e[Edge[i].b].push_back(Edge[i].c);
        MST += Edge[i].c;
    }
}
void dfs1(int u,int f)
{
    depth[u] = depth[f] + 1;
    fat[u] = f;
    siz[u] = 1;
    int maxn = 0,maxx = 0;
    for(int i=0;i<g[u].size();i++)
    {
        int v = g[u][i];
        if(v == f) continue;
        a[v] = e[u][i];
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
void dfs2(int u,int f)
{
    if(!son[u]) return;
    top[son[u]] = top[u];
    seg[son[u]] = ++tot;
    rev[tot] = son[u];
    dfs2(son[u],u);
    for(int i=0;i<g[u].size();i++)
    {
        int v = g[u][i];
        if(v != f && v != son[u])
        {
            top[v] = v;
            seg[v] = ++tot;
            rev[tot] = v;
            dfs2(v,u);
        }
    }
}
void build(int p,int l,int r)
{
    tree[p].l = l;
    tree[p].r = r;
    if(l == r) 
    {
        tree[p].maxx = a[rev[l]];
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    tree[p].maxx = max(tree[p<<1].maxx,tree[p<<1|1].maxx);
}
int query(int p,int x,int y)
{
    if(x > y) return 0;
    if(tree[p].l >= x && tree[p].r <= y) return tree[p].maxx;
    int ans = 0;
    int mid = (tree[p].l+tree[p].r) >> 1;
    if(x <= mid) ans = max(ans,query(p<<1,x,y));
    if(mid < y) ans = max(ans,query(p<<1|1,x,y));
    return ans;
}
int query_path(int x,int y)
{
    int ans = 0;
    while(top[x] != top[y])
    {
        if(depth[top[x]] < depth[top[y]]) swap(x,y);
        ans = max(ans,query(1,seg[top[x]],seg[x]));
        x = fat[top[x]];
        if(!x) x = 1;
    }
    if(depth[x] > depth[y]) swap(x,y);
    ans = max(ans,query(1,seg[son[x]],seg[y]));
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++) 
    {
        int a,b,c;
        cin>>a>>b>>c;
        Edge[i] = {a,b,c};
        d[i] = Edge[i];
    }
    sort(Edge+1,Edge+m+1,cmp);
    kruskal();
    dfs1(1,0);
    top[1] = seg[1] = rev[1] = 1;
    dfs2(1,0);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        cout<<MST + d[i].c-query_path(d[i].a,d[i].b)<<endl;
    }
    return 0;
}