#include <bits/stdc++.h>
using namespace std;
namespace solution
{
    #define int long long
    constexpr int N = 1000010;
    int n,q;
    int a[N];
    struct segtree
    {
        int cnt = 1;
        struct TREE
        {
            int l,r,sum,tag;
        }tree[N];
        void pushup(int &p) {tree[p].sum = tree[tree[p].l].sum + tree[tree[p].r].sum;}
        void pushdown(int p,int l,int r)
        {
            if(!tree[p].tag) return;
            if(!tree[p].l) tree[p].l = ++cnt;
            if(!tree[p].r) tree[p].r = ++cnt;
            int mid = (l+r) >> 1;
            tree[tree[p].l].sum +=(mid-l+1)*tree[p].tag;
            tree[tree[p].r].sum += (r-mid)*tree[p].tag;
            tree[tree[p].l].tag += tree[p].tag;
            tree[tree[p].r].tag += tree[p].tag;
            tree[p].tag = 0;
        }
        void update(int l,int r,int pos,int &p,int d)
        {
            if(!p) p = ++cnt;
            if(l == r) 
            {
                tree[p].sum = d;
                return;
            }
            int mid = (l+r) >> 1;
            if(pos <= mid) update(l,mid,pos,tree[p].l,d);
            if(pos > mid) update(mid+1,r,pos,tree[p].r,d);
            pushup(p);
        }
        void modify(int l,int r,int pl,int pr,int &p,int d)
        {
            if(!p) p = ++cnt;
            if(l >= pl && r <= pr) 
            {
                tree[p].sum += (r-l+1)*d;
                tree[p].tag += d;
                return;
            }
            int mid = (l+r) >> 1;
            pushdown(p,l,r);
            if(pl <= mid) 
                modify(l,mid,pl,pr,tree[p].l,d);
            if(pr > mid)
                modify(mid+1,r,pl,pr,tree[p].r,d);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(!p) return 0;
            if(l >= pl && r <= pr) return tree[p].sum;
            int mid = (l+r) >> 1;
            pushdown(p,l,r);
            int ans = 0;
            if(pl <= mid) ans += query(l,mid,pl,pr,tree[p].l);
            if(pr > mid) ans += query(mid+1,r,pl,pr,tree[p].r);
            return ans;
        }
    }seg;
    void solve()
    {
        cin>>n>>q;
        for(int i=1;i<=n;i++) 
        {
            cin>>a[i];
            int p = 1;
            seg.update(1,n,i,p,a[i]);   
        }
        while(q--)
        {
            int op,x,y,k;
            cin>>op>>x>>y;
            if(op == 1) 
            {
                cin>>k;
                int qwq = 1;
                seg.modify(1,n,x,y,qwq,k);
            }
            else cout<<seg.query(1,n,x,y,1)<<endl;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}