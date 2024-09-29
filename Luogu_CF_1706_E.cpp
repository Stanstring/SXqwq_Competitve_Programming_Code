#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 100010;
constexpr int INF = 0x3f3f3f3f;
int T;
int n,m,q;
vector <int> Edge[N];
int fa[N],siz[N];
int minn[N];
int tree[N];
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void build(int l,int r,int p)
{
    if(l == r) 
    {
        tree[p] = minn[l];
        return;
    }
    int mid = (l+r) >> 1;
    build(l,mid,p*2);
    build(mid+1,r,p*2+1);
    tree[p] = max(tree[p*2],tree[p*2+1]);
}
int query(int l,int r,int pl,int pr,int p)
{
    if(l > pr || r < pl) return 0;
    if(l >= pl && r <= pr) return tree[p];
    int mid = (l+r) >> 1;
    return max(query(l,mid,pl,pr,p*2),query(mid+1,r,pl,pr,p*2+1));
}
void solve()
{
    cin>>n>>m>>q;
    memset(tree,0,sizeof(tree));
   // memset(minn,INF,sizeof(minn));
   // fa[n+1] = n+1;
    for(int i=1;i<=n;i++)
    {
        Edge[i].clear();
        Edge[i].push_back(i);
        fa[i] = i;
        siz[i] = 1;
        minn[i] = INF;
    } 
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        x = find(x),y = find(y);
        if(x == y) continue;
        if(siz[x] > siz[y]) swap(x,y);
        siz[y] += siz[x];
        fa[x] = y;
        for(int t = 0;t < Edge[x].size();t++)
        {
            int v = Edge[x][t];
            if(find(v) == find(v+1)) minn[v] = min(i,minn[v]);
            if(find(v) == find(v-1)) minn[v-1] = min(minn[v-1],i);
            Edge[y].push_back(v);
        }   
        Edge[x].clear();
        siz[x] = 0;
    }
    build(1,n-1,1);
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<query(1,n-1,l,r-1,1)<<" ";
    }
    cout<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
    {
        solve();
    }
}