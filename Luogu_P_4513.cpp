#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 10000010;
int n,m;
struct segment_tree
{
    struct Node
    {
        int ml,mr,mx,sum;
    }tree[N];
    void pushup(int p)
    {
        tree[p].ml = max(tree[p<<1].ml,tree[p<<1].sum + tree[p<<1|1].ml);
        tree[p].mr = max(tree[p<<1|1].mr,tree[p<<1|1].sum + tree[p<<1].mr);
        tree[p].mx = max({tree[p<<1].mr+tree[p<<1|1].ml,tree[p<<1].mx,tree[p<<1|1].mx});
        tree[p].sum = tree[p<<1].sum + tree[p<<1|1].sum;
    }
    void build(int l=1,int r=n,int p=1)
    {
        if(l == r)
        {
            int t;
            cin>>t;
            tree[p].ml = tree[p].mr = tree[p].sum = tree[p].mx = t;
            return;
        }
        int mid = (l+r) >> 1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        pushup(p);
    }
    void modify(int l,int r,int pos,int p,int d)
    {
        if(l == r)
        {
          //  if(l != pos) return;
            tree[p].ml = tree[p].mr = tree[p].mx = tree[p].sum = d;
            return;
        }
        int mid = (l+r) >> 1;
        if(pos <= mid) modify(l,mid,pos,p<<1,d);
        else modify(mid+1,r,pos,p<<1|1,d);
        pushup(p);
    }
    Node query(int l,int r,int pl,int pr,int p)
    {
        if(l >= pl && r <= pr) return tree[p];
        int mid = (l+r) >> 1;
        if(pr <= mid) return query(l,mid,pl,pr,p<<1);
        if(pl > mid) return query(mid+1,r,pl,pr,p<<1|1);
        Node qwq = query(l,mid,pl,pr,p<<1),qaq = query(mid+1,r,pl,pr,p<<1|1),rtn;
        rtn.ml = max(qwq.ml,qwq.sum + qaq.ml);
        rtn.mr = max(qaq.mr,qaq.sum + qwq.mr);
        rtn.mx = max({qwq.mr+qaq.ml,qwq.mx,qaq.mx});
        return rtn;
    }
}sgt;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    sgt.build();
    for(int i=1;i<=m;i++)
    {
        int op;
        cin>>op;
        if(op == 1) 
        {
            int l,r;
            cin>>l>>r;
            if(l > r) swap(l,r);
            cout<<sgt.query(1,n,l,r,1).mx<<endl;
        }
        else
        {
            int p,x;
            cin>>p>>x;
            sgt.modify(1,n,p,1,x);
        }
    }
}