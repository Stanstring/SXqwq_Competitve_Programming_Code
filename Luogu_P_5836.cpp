#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PAIR;
constexpr int N = 1000010;
int n,m;
int a[N],val[N];
int cnt = 0;
vector <int> Edge[N];
int dfn[N],siz[N],son[N],depth[N],fat[N],tp[N];
struct segtree
{
    #define ls p<<1
    #define rs p<<1|1
    int tree[N];
    void pushup(int p){tree[p] = tree[ls] + tree[rs];}
    void build(int l = 1,int r = n,int p = 1)
    {
        if(l == r) 
        {
            tree[p] = a[l];
            return;
        }
        int mid = (l+r) >> 1;
        build(l,mid,ls);
        build(mid+1,r,rs);
        pushup(p);
    }
    int query(int l,int r,int pl,int pr,int p)
    {
        if(l > pr || r < pl) return 0;
        if(l >= pl && r <= pr) return tree[p];
        int mid = (l+r) >> 1;
        return query(l,mid,pl,pr,ls) + query(mid+1,r,pl,pr,rs);
    }
}seg;
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
    a[cnt] = val[u];
    if(!son[u]) return;
    dfs2(son[u],topp);
    for(auto v:Edge[u])
    {
        if(v == fat[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
PAIR query(int x,int y)
{
    int sum = 0;
    while(tp[x] != tp[y])
    {
        if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
        sum += seg.query(1,n,dfn[tp[y]],dfn[y],1);
        y = fat[tp[y]];
    }
    if(depth[x] > depth[y]) swap(x,y);
    sum += seg.query(1,n,dfn[x],dfn[y],1);
    return PAIR(sum,x);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        char ch;
        cin>>ch;
        if(ch == 'H') val[i] = 1;
    }  
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    seg.build();
    while(m--)
    {
        int u,v,w;
        char ch;
        cin>>u>>v>>ch;
        PAIR res = query(u,v);
     //   cout<<res.first<<" "<<res.second<<endl;
        if(ch == 'H')
            cout<<(res.first >= 1);
        else
        {
          //  cout<<res.first<<" "<<(depth[u]+depth[v]-(depth[res.second]*2))<<endl;
            cout<<(res.first < (depth[u]+depth[v]-(depth[res.second]*2))+1);
        }
    }
    cout<<endl;
    return 0;
}