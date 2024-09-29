#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int mod = 201314;
namespace solution
{
    int n,m;
    int ans[N];
    vector <int> Edge[N];
    struct Node
    {
        int pos,z,id,flg;
        bool operator<(const Node& a)const{
            return pos < a.pos;
        }
    };
    vector <Node> q;
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N],tag[N];
        void pushdown(int p,int len)
        {
            if(!tag[p]) return;
            tree[ls] += (len-len/2)*tag[p],tree[rs] += (len/2)*tag[p];
            tag[ls] += tag[p],tag[rs] += tag[p];
            tag[p] = 0;
        }
        void pushup(int p){tree[p] = tree[ls] + tree[rs];}
        void modify(int l,int r,int pl,int pr,int p,int d)
        {
            if(l > pr || r < pl) return;
            if(l >= pl && r <= pr) {tree[p] += (r-l+1)*d;tag[p] += d;return;}
            int mid = (l+r) >> 1;
            pushdown(p,r-l+1);
            modify(l,mid,pl,pr,ls,d);
            modify(mid+1,r,pl,pr,rs,d);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return 0;
            if(l >= pl && r <= pr) return tree[p];
            int mid = (l+r) >> 1;
            pushdown(p,r-l+1);
            return query(l,mid,pl,pr,ls) + query(mid+1,r,pl,pr,rs);
        }
    }seg;
    struct TCS
    {
        int dfn[N],siz[N],depth[N],son[N],tp[N],fa[N];
        int cnt = 0;
        void dfs1(int u,int f)
        {
            depth[u] = depth[f] + 1;
            siz[u] = 1;
            fa[u] = f;
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
                if(v == fa[u] || v == son[u]) continue;
                dfs2(v,v);
            }
        }
        void modify(int x,int y,int d)
        {
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                seg.modify(1,n,dfn[tp[y]],dfn[y],1,d);
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            seg.modify(1,n,dfn[x],dfn[y],1,d);
            return;
        }
        int query(int x,int y)
        {
            int sum = 0;
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                sum += seg.query(1,n,dfn[tp[y]],dfn[y],1);
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            sum += seg.query(1,n,dfn[x],dfn[y],1);
            return sum;
        }
    }tcs;
    void solve()
    {
        cin>>n>>m;
        for(int i=2;i<=n;i++) 
        {
            int f;
            cin>>f;
            f ++;
            Edge[f].push_back(i);
            Edge[i].push_back(f);
        }
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        for(int i=1;i<=m;i++)
        {
            int l,r,z;
            cin>>l>>r>>z;
            l ++;
            r ++;
            z ++;
            q.push_back({l-1,z,i,0});
            q.push_back({r,z,i,1});
        }
        sort(q.begin(),q.end());
        int pos = 1;
        for(auto t:q)
        {
            while(pos <= t.pos) tcs.modify(1,pos++,1);
            if(t.flg) ans[t.id] += tcs.query(1,t.z);
            else ans[t.id] -= tcs.query(1,t.z);
            ans[t.id] += mod;
            ans[t.id] %= mod;
        }
        for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
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