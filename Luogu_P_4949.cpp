#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
constexpr int N = 1000010;
typedef pair<int,int> PAIR;
struct Node
{
    int u,v,w;
    int number;
}qwq[N];
int n,q;
vector <PAIR> Edge[N];
map <int,PAIR> m;
int fa[N];
int etcu,etcv,etcw,etcnum; //extra edge
int dfn[N],fat[N],siz[N],a[N],son[N],tp[N],depth[N],val[N];
int cnt = 0;
int tree[N];
int mark[N];
void init(){for(int i=1;i<=n;i++) fa[i] = i;}
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void dfs1(int u,int f)
{
    siz[u] = 1;
    fat[u] = f;
    depth[u] = depth[f] + 1;
    int maxn = 0,maxx = 0;
    for(auto t:Edge[u])
    {
        int v = t.x,w = t.y;
        if(v == f) continue;
        val[v] = w;
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
    a[cnt] = val[u];
    tp[u] = topp;
    if(!son[u]) return;
    dfs2(son[u],topp);
    for(auto t:Edge[u])
    {
        int v = t.x,w = t.y;
        if(v == fat[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
//segment tree
void build(int l,int r,int p)
{
    if(l == r)
    {
        tree[p] = a[l];
        return;
    }
    int mid = (l+r) /2;
    build(l,mid,p*2);
    build(mid+1,r,p*2+1);
    tree[p] = tree[p*2]+tree[p*2+1];
}
void modify(int l,int r,int pos,int p,int d)
{
    if(l == r) {tree[p] = d;return;}
    int mid = (l+r) /2;
    if(pos <= mid)
        modify(l,mid,pos,p*2,d);
    else
        modify(mid+1,r,pos,p*2+1,d);
    tree[p] = tree[p*2]+tree[p*2+1];
}
int query(int l,int r,int pl,int pr,int p)
{
    int ans = 0;
    if(l > pr || r < pl) return 0;
    if(l >= pl && r <= pr) return tree[p];
    int mid = (l+r) /2;
    return query(l,mid,pl,pr,p*2) + query(mid+1,r,pl,pr,p*2+1);
}
//segment tree
int query_path(int u,int v)
{
    int ans = 0;
    while(tp[u] != tp[v])
    {
        if(depth[tp[u]] > depth[tp[v]]) swap(u,v);
        ans += query(1,n,dfn[tp[v]],dfn[v],1);
        v = fat[tp[v]];  
    }
    if(u == v) return ans;
    if(depth[u] > depth[v]) swap(u,v);
    ans += query(1,n,dfn[u]+1,dfn[v],1);
   // cout<<ans<<"qwq"<<endl;
    return ans;
}
void solve()
{
    while(q--)
    {
        int op,x,y;
        cin>>op>>x>>y;
       // if(x > y) swap(x,y);
        if(op == 1)
        {
            int nx = m[x].x,ny = m[x].y;
            if(nx == etcu && ny == etcv || (nx == etcv && ny == etcu)) 
            {
                etcw = y;
                continue;
            }
            if(nx == fat[ny]) swap(nx,ny);
            modify(1,n,dfn[nx],1,y);
        }
        else
        {
            int qaq = query_path(x,y);
            int quq = query_path(x,etcu)+etcw + query_path(etcv,y);
            int aya = query_path(x,etcv) + etcw + query_path(etcu,y);
            cout<<min({qaq,quq,aya})<<endl;
        }
    }
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    init();
    for(int i=1;i<=n;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;   
        qwq[i] = {u,v,w,i};
        m[i] = PAIR(u,v);
    }
    for(int i=1;i<=n;i++)
    {
        Node p = qwq[i];
        int u = p.u,v = p.v,w = p.w;
        int uu = find(u),vv = find(v);
        if(uu == vv) 
        {
            if(u > v) swap(u,v);
            etcu = u,etcv = v,etcw = w,etcnum = p.number;
            continue;
        }
        fa[uu] = fa[vv];
        Edge[u].push_back(PAIR(v,w));
        Edge[v].push_back(PAIR(u,w));
    }   
    dfs1(1,0);
    dfs2(1,0);
    build(1,n,1);
    solve();
    return 0;
}