#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    int L[N];
    int n;
    struct LINE
    {
        int l,r,h,tag;
        bool operator<(const LINE& a)const{
            return h < a.h;
        }
    }line[N*16];
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        struct TREE
        {
            int l,r,sum,len;
        }tree[N*16];
        void pushup(int p)
        {
            int l = tree[p].l,r = tree[p].r;
            if(tree[p].sum)
                tree[p].len = L[r+1] - L[l];
            else tree[p].len = tree[ls].len + tree[rs].len; 
        }
        void build(int l,int r,int p)
        {
            
            tree[p].l = l;
            tree[p].r = r;
            tree[p].len = tree[p].sum = 0;
            int mid = (l+r) >> 1;
            if(l == r) return;
            build(l,mid,ls);
            build(mid+1,r,rs);
            return;
        }
        void modify(int LL,int RR,int p,int d)
        {
            int l = tree[p].l,r = tree[p].r;
            if(LL >= L[r+1] || RR <= L[l]) return;
            if(L[l] >= LL && L[r+1] <= RR) 
            {
                tree[p].sum += d;
                pushup(p);
                return;
            }
            modify(LL,RR,ls,d);
            modify(LL,RR,rs,d);
            pushup(p);
        }
    }seg;
    void solve()
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            int xa,ya,xb,yb;
            cin>>xa>>ya>>xb>>yb;
            L[i*2-1] = xa,L[i*2] = xb;
            line[i*2-1] = {xa,xb,ya,1};
            line[i*2] = {xa,xb,yb,-1};
        }
        n <<= 1;
        sort(line+1,line+n+1);
        sort(L+1,L+n+1);
        int tot = unique(L+1,L+n+1) - L - 1;
      //  cerr<<tot<<endl;
        seg.build(1,tot-1,1);
        int ans = 0;
        for(int i=1;i<n;i++)
        {
            seg.modify(line[i].l,line[i].r,1,line[i].tag);
            ans +=( seg.tree[1].len *(line[i+1].h-line[i].h));
        }
        cout<<ans<<endl;
        return;
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