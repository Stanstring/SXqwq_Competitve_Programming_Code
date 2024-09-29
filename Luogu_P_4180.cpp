#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
constexpr int N = 10000010;
constexpr int INF = 1e15;
typedef pair<int,int> PAIR;
struct Node
{
    int u,v,w,tag;
    bool operator <(const Node &a)const{
        return w < a.w;
    }
};
int n,m;
vector <PAIR> Edge[N];
vector <Node> qwq;
vector <Node> EDGE;
int fa[N];
int MST = 0;
int dfn[N],siz[N],depth[N],son[N],tp[N],fat[N],val[N],a[N];
int cnt = 0;
PAIR tree[N];
int ans = INF;
void init(){for(int i=1;i<=n;i++) fa[i] = i;}
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void kruskal()
{
    int count = 0;
    for(auto &t:qwq)
    {
        int u = t.u,v = t.v,w = t.w;
        int fu = find(u),fv = find(v);
        if(fu == fv) 
        {
          //  cout<<"/qq"<<endl;
          //  t.tag = 1;
            continue;
        }
        t.tag = 1;
      //  cout<<u<<" "<<v<<endl;
        Edge[u].push_back(PAIR(v,w));
        Edge[v].push_back(PAIR(u,w));
        MST += w;
        fa[fu] = fv;
        if(++count == n-1) return;
    }
}
bool CMP(int a,int b){return a > b;}
inline int getse(int q,int w,int e,int r)
{
    int qaq[5] = {q,w,e,r};
    sort(qaq,qaq+4,CMP);
    for(int i = 1;i < 3;i++)
        if(qaq[i] != qaq[0]) return qaq[i];
    return 0;
}
void dfs1(int u,int f)
{
    depth[u] = depth[f] + 1;
    siz[u] = 1;
    fat[u] = f;
    int maxn = 0,maxx = 0;
   // cout<<Edge[u].size()<<endl;
    for(auto t:Edge[u])
    {
        int v = t.x,w = t.y;
      //  cout<<val[v]<<"qwq"<<endl;
        if(v == f) continue;
        val[v] = w;
      //  cout<<val[v]<<endl;
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
void build(int l,int r,int p)
{
    if(l == r) 
    {
        tree[p].x = a[l];
      //  cout<<tree[p]<<endl;
        return;
    }
    int mid = (l+r) >> 1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    tree[p].x = max(tree[p<<1].x,tree[p<<1|1].x);
    tree[p].y = getse(tree[p<<1].x,tree[p<<1|1].x,tree[p<<1].y,tree[p<<1|1].y);
}
PAIR query(int l,int r,int pl,int pr,int p)
{
    if(l > pr || r < pl) return PAIR(-INF,-INF);
    if(l >= pl && r <= pr) return PAIR(tree[p].x,tree[p].y);
    int mid = (l+r) >> 1;
    PAIR t1 = query(l,mid,pl,pr,p<<1),t2 = query(mid+1,r,pl,pr,p<<1|1);
    return PAIR(max(t1.x,t2.x),getse(t1.x,t2.x,t1.y,t2.y));
}
int query_path(int a,int b,int d)
{
    int maxn = -INF;
    while(tp[a] != tp[b])
    {
        if(depth[tp[a]] > depth[tp[b]]) swap(a,b);
        PAIR tmp = query(1,n,dfn[tp[b]],dfn[b],1);
        b = fat[tp[b]];
        maxn = max(maxn,(tmp.x==d)?tmp.y:tmp.x);
    }
    if(depth[a] > depth[b]) swap(a,b);
    PAIR tmp = query(1,n,dfn[a]+1,dfn[b],1);
    return max(maxn,(tmp.x==d)?tmp.y:tmp.x);
}
void solve()
{
  //  cout<<EDGE.size()<<endl;
    for(auto t:EDGE)
    {
        int u = t.u,v = t.v,w = t.w;
        int maxn = query_path(u,v,w);
        if(maxn == w) continue;
       // cout<<maxn<<endl;
       int tmp = MST + w - maxn;
       if(ans > tmp && tmp != MST  + w && tmp > MST) ans = tmp;
     }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   // memset(a,INF,sizeof(a));
 //   memset(val,INF,sizeof(val));
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        qwq.push_back({u,v,w,0});
    }
    sort(qwq.begin(),qwq.end());
    kruskal();
    dfs1(1,0);
    dfs2(1,0);
    build(1,n,1);
    for(auto t:qwq)
        if(!t.tag) EDGE.push_back(t);
    solve();
   //cout<<MST<<endl;
    cout<<ans<<endl;
    return 0;
}