#include <bits/stdc++.h>
using namespace std;
constexpr int N = 10000010;
int n,m;
double a[N];
struct segtree
{
    #define ls p<<1
    #define rs p<<1|1
    struct Node
    {
        double sum,tag;
    }tree1[N],tree2[N];
    void pushup(int p)
    {
        tree1[p].sum = tree1[ls].sum + tree1[rs].sum;
        tree2[p].sum = tree2[ls].sum + tree2[rs].sum;
    }
    void pushdown(int p,int l,int r)
    {
        int mid = (l+r) >> 1;
        tree2[ls].tag += tree2[p].tag;
        tree2[ls].sum += tree1[ls].sum * (tree2[p].tag*2)+(mid-l+1) * (tree2[p].tag*tree2[p].tag);
        tree2[rs].tag += tree2[p].tag;
        tree2[rs].sum += tree1[rs].sum * (tree2[p].tag*2)+(r-mid) * (tree2[p].tag*tree2[p].tag);
        tree2[p].tag = 0;
        tree1[ls].tag += tree1[p].tag;
        tree1[ls].sum += (mid-l+1)*tree1[p].tag;
        tree1[rs].tag += tree1[p].tag;
        tree1[rs].sum += (r-mid)*tree1[p].tag;
        tree1[p].tag = 0;
    }
    void build(int l,int r,int p)
    {
        if(l == r)
        {
            tree1[p].sum = a[l];
            tree2[p].sum = a[l] * a[l];
            return;
        }
        int mid = (l+r) >> 1;
        build(l,mid,ls);
        build(mid+1,r,rs);
        pushup(p);
    }
    double query(Node tree[],int l,int r,int pl,int pr,int p)
    {
        if(l >= pl && r <= pr) return tree[p].sum;
        int mid = (l+r) >> 1;
        if(tree[p].tag) pushdown(p,l,r);
        double ans = 0;
        if(pl <= mid) ans += query(tree,l,mid,pl,pr,ls);
        if(pr > mid) ans += query(tree,mid+1,r,pl,pr,rs);
        pushup(p);
        return ans;
    }
    void modify(int l,int r,int pl,int pr,int p,double d)
    {
        if(l >= pl && r <= pr) 
        {
            tree2[p].tag += d;
            tree2[p].sum += tree1[p].sum * (d*2)+(r-l+1)*(d*d);
            tree1[p].tag += d;
            tree1[p].sum += (r-l+1)*d;
            return;
        }
        if(tree1[p].tag || tree2[p].tag) pushdown(p,l,r);
        int mid = (l+r) >> 1;
        if(pl <= mid) modify(l,mid,pl,pr,ls,d);
        if(pr > mid) modify(mid+1,r,pl,pr,rs,d);
        pushup(p);
    }
}seg;
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    seg.build(1,n,1);
    while(m--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int x,y;
            double t;
            cin>>x>>y>>t;
            seg.modify(1,n,x,y,1,t);
        }
        // if(op == 2)
        // {
        //     int x,y;
        //     cin>>x>>y;
        //     printf("%.4lf\n",seg.query(seg.tree1,1,n,x,y,1)/(y-x+1)*1.0);
        // }
        if(op == 2)
        {
            int x,y;
            cin>>x>>y;
            printf("%.4lf\n",(seg.query(seg.tree2,1,n,x,y,1)/(y-x+1)*1.0)-((seg.query(seg.tree1,1,n,x,y,1)/(y-x+1)*1.0)*(seg.query(seg.tree1,1,n,x,y,1)/(y-x+1)*1.0)));
        }
    }
    return 0;
}