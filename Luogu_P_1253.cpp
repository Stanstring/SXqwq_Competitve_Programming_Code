#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 5e6;
constexpr int INF = -1e15;
namespace solution
{
    int n,q;
    int a[N];
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        struct Node
        {
            int maxn,covertag = INF,sumtag;
           // covertag = INF;
        }tree[N];
        void pushup(int p){tree[p].maxn = max(tree[ls].maxn,tree[rs].maxn);}
        void coverdown(int p)
        {
            if(tree[p].covertag == INF) return;
            tree[ls].sumtag = tree[rs].sumtag = 0;
            tree[ls].maxn = tree[rs].maxn = tree[p].covertag;
            tree[ls].covertag = tree[rs].covertag = tree[p].covertag;
            tree[p].covertag = INF;
        }
        void sumdown(int p)
        {
            if(!tree[p].sumtag) return;
            tree[ls].maxn += tree[p].sumtag;
            tree[rs].maxn += tree[p].sumtag;
            tree[ls].sumtag += tree[p].sumtag;
            tree[rs].sumtag += tree[p].sumtag;
            tree[p].sumtag = 0;
        }
        void pushdown(int p){coverdown(p);sumdown(p);}
        void build(int l = 1,int r = n,int p = 1)
        {
            if(l == r) 
            {
                tree[p].maxn = a[l];
                tree[p].covertag = INF;
                return;
            }
            int mid = (l+r) >> 1;
            build(l,mid,ls);
            build(mid+1,r,rs);
            pushup(p);
        }
        void modify_cover(int l,int r,int pl,int pr,int p,int d)
        {
            if(l > pr || r < pl) return;
            if(l >= pl && r <= pr) 
            {
                tree[p].sumtag = 0;
                tree[p].maxn = d;
                tree[p].covertag = d;
                return;
            }
            int mid = (l+r) >> 1;   
            pushdown(p);
            modify_cover(l,mid,pl,pr,ls,d);
            modify_cover(mid+1,r,pl,pr,rs,d);
            pushup(p);
        }
        void modify_sum(int l,int r,int pl,int pr,int p,int d)
        {
            if(l > pr || r < pl) return;
            if(l >= pl && r <= pr) 
            {
              //  coverdown(p);
                tree[p].maxn += d;
                tree[p].sumtag += d;
                return;
            }
            int mid = (l+r) >> 1;
            pushdown(p);
            modify_sum(l,mid,pl,pr,ls,d);
            modify_sum(mid+1,r,pl,pr,rs,d);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return INF;
            if(l >= pl && r <= pr) return tree[p].maxn;
            int mid = (l+r) >> 1;
            pushdown(p);
            return max(query(l,mid,pl,pr,ls),query(mid+1,r,pl,pr,rs));
        }
    }seg;
    void solve()
    {
        cin>>n>>q;
        for(int i=1;i<=n;i++) cin>>a[i];
        seg.build();
        while(q--)
        {
            int op,l,r,x;
            cin>>op>>l>>r;
            if(op == 1)
            {
                cin>>x;
                seg.modify_cover(1,n,l,r,1,x);
            }
            else if(op == 2)
            {
                cin>>x;
                seg.modify_sum(1,n,l,r,1,x);
            }
            else cout<<seg.query(1,n,l,r,1)<<endl;
        }
        return;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}