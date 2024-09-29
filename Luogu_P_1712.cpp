#include <bits/stdc++.h>
using namespace std;
constexpr int N = 10000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        struct TREE
        {
            int sum,maxn;
        }tree[N];
        void modify_dot(int p,int d){tree[p].maxn += d;tree[p].sum += d;}
        void pushup(int p){tree[p].maxn = max(tree[ls].maxn,tree[rs].maxn);}
        void pushdown(int p)
        {
            if(!tree[p].sum) return;
            modify_dot(ls,tree[p].sum);
            modify_dot(rs,tree[p].sum);
            tree[p].sum = 0;
        }
        void modify(int l,int r,int pl,int pr,int p,int d)
        {
            if(l > pr || r < pl) return;
            if(l >= pl && r <= pr)
            {
                modify_dot(p,d);
                return;
            }
            int mid = (l+r) >> 1;
            pushdown(p);
            modify(l,mid,pl,pr,ls,d);
            modify(mid+1,r,pl,pr,rs,d);
            pushup(p);
        }
    }seg;
    struct Node
    {
        int l,r,len;
        bool operator <(const Node& a)const{
            return len < a.len;
        }
    }opt[N];
    int n,m,cnt = 0;
    int val[N];
    int minl = INF,maxr = 0;
    void discretizing()
    {
        sort(val+1,val+cnt+1);
        int x = unique(val+1,val+cnt+1)-val-1;
        sort(opt+1,opt+n+1);
        for(int i=1;i<=n;i++)
        {
            opt[i].l = lower_bound(val+1,val+x+1,opt[i].l)-val;
            opt[i].r = lower_bound(val+1,val+x+1,opt[i].r)-val;
            minl = min(minl,opt[i].l);
            maxr = max(maxr,opt[i].r);
        }
    }
    void solve()
    {
        int ans = INF;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            cin>>opt[i].l>>opt[i].r;
            opt[i].len = opt[i].r - opt[i].l;
            val[++cnt] = opt[i].l,val[++cnt] = opt[i].r;
        }
        discretizing();
        int nowl = 1;
        for(int i=1;i<=n;i++)
        {
            seg.modify(minl,maxr,opt[i].l,opt[i].r,1,1);
            while(seg.tree[1].maxn >= m)
            {
                ans = min(ans,opt[i].len-opt[nowl].len);
                seg.modify(minl,maxr,opt[nowl].l,opt[nowl].r,1,-1);
                nowl ++;
            }
        }
        cout<<((ans == INF?-1:ans))<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}