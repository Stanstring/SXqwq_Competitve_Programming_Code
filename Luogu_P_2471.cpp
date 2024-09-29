#include <bits/stdc++.h>
#define int long long
    #define maybe cout<<"maybe"<<endl;continue;//让输出没这么难看
    #define false cout<<"false"<<endl;continue;
    #define true cout<<"true"<<endl;continue;
using namespace std;
constexpr int N = 10000010;
constexpr int INF = 0x3f3f3f3f;
map <int,int> m;
int a[N];
int cnt = 0;
int n,q;
int year[N],rain[N];
struct segtree
{
    #define ls p<<1
    #define rs p<<1|1
    int tree[N];
    void pushup(int p)
    {
        tree[p] = max(tree[ls],tree[rs]);
    }
    void modify(int l,int r,int pos,int p,int d)
    {
        if(l == r) 
        {
            tree[p] = d;
            return;
        }
        int mid =(l+r) >> 1;
        if(pos <= mid) modify(l,mid,pos,ls,d);
        else modify(mid+1,r,pos,rs,d);
        pushup(p);
    }
    int query(int l,int r,int pl,int pr,int p)
    {
        if(l > pr || r < pl) return 0;
        if(l >= pl && r <= pr) return tree[p];
        int mid = (l+r) >> 1;
        return max(query(l,mid,pl,pr,ls),query(mid+1,r,pl,pr,rs));
    }
}seg;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        int y,r;
        cin>>y>>r;
        year[i] = y;
        rain[i] = r;
        seg.modify(1,n,i,1,r);
    }
    cin>>q;
    while(q--)
    {
        int x,y;
        cin>>y>>x;
        //map <int,int> ::iterator p1,p2;
        int p1 = lower_bound(year+1,year+n+1,y)-year,p2= lower_bound(year+1,year+n+1,x)-year;
      //  cout<<p1->first<<endl;
        int f1 = (p1 == n + 1|| year[p1] != y) ? 0 : 1;
        int f2 = (p2 == n + 1 ||year[p2] != x) ? 0 : 1;
        if(!f1 && !f2){maybe}
        else if(f1 && !f2) 
        {
            if(p1+ 1 == p2) {maybe}
            int maxn = seg.query(1,n,p1 + 1,p2-1,1);
            if(maxn >= rain[p1]) {false}
            else {maybe}
        }
        else if(!f1 && f2)
        {
            if(p1 == p2) {maybe}
            int maxn = seg.query(1,n,p1,p2-1,1);
            if(maxn >= rain[p2]){false}
            else {maybe}
        }
        else
        {
            if(rain[p1] < rain[p2]) {false}
            if(y+1 == x) {true}
            if(p1 + 1 == p2) {maybe}
            int maxn = seg.query(1,n,p1+1,p2-1,1);
            if(maxn >= rain[p2]) {false}
            if(p2-p1 == x-y) {true}
            else {maybe}
        }
    }
}