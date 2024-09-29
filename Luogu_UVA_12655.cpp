#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
typedef pair<int,int> PAIR;
struct Node
{
    int u,v,w;
    bool operator<(const Node &a)const{
        return w > a.w;
    }
};
int val[N],fa[N],a[N]; // dsu
int fat[N],depth[N],son[N],siz[N],tp[N],dfn[N];// poufen
int tree[N]; 
int cnt;
int n,m;
int q;
int vis[N];
vector <PAIR> Edge[N];
vector <Node> qwq;
void init(){for(int i=1;i<=n;i++) fa[i] =  i;}
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void kruskal() // MST (MAX)
{
  //  int cnt = 0;
    for(auto t:qwq)
    {
        int u = t.u,v = t.v,w = t.w;
        int i = find(u),j = find(v);
        if(i == j) continue;
        //cout<<u<<" "<<v<<endl;
        fa[i] = fa[j];
        Edge[u].push_back(PAIR(v,w));
        Edge[v].push_back(PAIR(u,w));
       // cnt ++;
       // if(cnt >= n-1) break;
    }
}
void dfs1(int u,int f)
{
    vis[u] = 1;
    fat[u] = f;
    depth[u] = depth[f] + 1;
    siz[u] = 1;
    int maxn = 0,maxx = 0;
    for(auto t:Edge[u])
    {
        int v = t.x,w = t.y;
        if(v == f) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v] > maxn)
        {
            maxn = siz[v];
            maxx = v;
        }
        val[v] = w;
     //   cout<<v<<" "<<val[v]<<"qwq"<<endl;
    }
    son[u] = maxx;
}
void dfs2(int u,int topp)
{
    dfn[u] = ++cnt;
    tp[u] = topp;
    a[cnt] = val[u]; // hash
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
        tree[p] = a[l];
        return;
    }
    int mid = (l+r) /2;
    build(l,mid,p*2);
    build(mid+1,r,p*2+1);
    tree[p] = min(tree[p*2],tree[p*2+1]);
}
int query(int l,int r,int pl,int pr,int p)
{
    if(l > pr || r < pl) return INF;
    if(l >= pl && r <= pr) return tree[p];
    int mid = (l+r) /2;
    return min(query(l,mid,pl,pr,p*2),query(mid+1,r,pl,pr,p*2+1));
}
int query_path(int u,int v)
{
    int minn = INF;
    while(tp[u] != tp[v])
    {
        if(depth[tp[u]] > depth[tp[v]])
        {
            minn = min(minn,query(1,n,dfn[tp[u]],dfn[u],1));
            u = fat[tp[u]];
        }
        else 
        {
            minn = min(minn,query(1,n,dfn[tp[v]],dfn[v],1));
            v = fat[tp[v]];
        }
    }
    if(u == v) return minn;
  //  cout<<depth[u]<<" "<<depth[v]<<"qaq"<<endl;
    if(depth[u] > depth[v]) swap(u,v);
 //   cout<<dfn[u]+1<<" "<<dfn[v]<<endl;
   //  cout<<a[5]<<endl;
   //cout<<query(1,n,5,5,1)<<endl;
   minn = min(minn,query(1,n,dfn[u]+1,dfn[v],1));
    return minn;
}
void solve()
{
  //  int q;
  //  cin>>q;
    while(q--)
    {
        int u,v;
        cin>>u>>v;
        if(find(u) != find(v)) cout<<"-1"<<endl;
      //  int answer = query_path(u,v);
        //cout<<answer<<endl;
        else cout<<query_path(u,v)<<endl;
     //   cout<<a[dfn[4+1]]<<" "<<a[dfn[5]]<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while(cin>>n>>m>>q)
    {
        cnt = 0;
//  cin>>n>>m;
   // memset(a,0x3f,sizeof(a));
   // memset(tree,0,sizeof(tree));
  // fill(vis+1,vis+1+n,0);
   // memset(vis,0,sizeof(vis));
    init();
    qwq.clear();
    for(int i=1;i<=n;i++) Edge[i].clear(),vis[i] = 0,tree[i] = 0;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        qwq.push_back({u,v,w});
        qwq.push_back({v,u,w});
    }
    sort(qwq.begin(),qwq.end());
    kruskal();
    for(int i=1;i<=n;i++) 
    {
        if(!vis[i]) 
        {
            dfs1(i,0);
            dfs2(i,0);
        }
    }
    build(1,n,1);
    solve();
    }
  
    return 0;
}