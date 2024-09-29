#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long
#define lc p<<1
#define rc p<<1|1
using namespace std;
const int N = 1000005;
struct Node
{
    ll v,lz1=1,lz2;
}tree[N<<2];
int n,q,m=1;
int a[N];
void build(int l,int r,int p)
{
    if(l == r) 
    {
        tree[p].v = a[l];
        return;
    }
    int mid = (l+r) / 2 ;
    build(l,mid,lc);
    build(mid+1,r,rc);
    tree[p].v = tree[lc].v + tree[rc].v;
}
void pushdown(int p,int l,int r)
{
    int mid=l+r>>1;
    ll &lz1=tree[p].lz1,&lz2=tree[p].lz2;
	if(lz1!=1){
		tree[lc].lz2=tree[lc].lz2*lz1%m;
        tree[rc].lz2=tree[rc].lz2*lz1%m;
		tree[lc].lz1=tree[lc].lz1*lz1%m;
        tree[rc].lz1=tree[rc].lz1*lz1%m;
		tree[lc].v=tree[lc].v*lz1%m;
        tree[rc].v=tree[rc].v*lz1%m;
		lz1=1;
	}
	if(lz2){
		tree[lc].v=(tree[lc].v+(mid-l+1)*lz2)%m;
        tree[lc].lz2=(tree[lc].lz2+lz2)%m;
		tree[rc].v=(tree[rc].v+(r-mid)*lz2)%m;
        tree[rc].lz2=(tree[rc].lz2+lz2)%m;
		lz2=0;
	}
}
void update1(int l,int r,int pl,int pr,int d,int p)
{
    if(pl > r || pr < l) return;
    if(pl >= l && pr <= r)
    {
        tree[p].lz1 = tree[p].lz1 * d % m;
        tree[p].lz2 = tree[p].lz2 * d % m;
        tree[p].v = (tree[p].v *d) % m;
        return;
    }
    int mid = (pl+pr) >> 1;
    pushdown(p,pl,pr);
    update1(l,r,pl,mid,d,lc);
    update1(l,r,mid+1,pr,d,rc);
    tree[p].v = tree[lc].v + tree[rc].v;
}
void update2(int l,int r,int pl,int pr,int d,int p)
{
    if(pl > r || pr < l) return;
    if(pl >= l && pr <= r)
    {
        tree[p].lz2 = (tree[p].lz2 + d) % m;
        tree[p].v = (tree[p].v + (pr-pl+1)*d) % m;
        return;
    }
    int mid = (pl+pr) >> 1;
    pushdown(p,pl,pr);
    update2(l,r,pl,mid,d,lc);
    update2(l,r,mid+1,pr,d,rc);
    tree[p].v = (tree[lc].v + tree[rc].v) % m;
}
__int128_t query(int l,int r,int pl,int pr,int p)
{
    if(pl > r || pr < l) return 0;
    if(pl >= l && pr <= r)
    {
        return tree[p].v;
    }
    int mid = (pl+pr) >> 1;
    pushdown(p,pl,pr);
    return (query(l,r,pl,mid,lc) + query(l,r,mid+1,pr,rc))%m;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }   
    cin>>q;
    build(1,n,1);
    while(q--)
    {
        int flg,x,y,k;
        cin>>flg;
        if(flg == 1) 
        {
            cin>>x>>y>>k;
            update1(x,y,1,n,k,1);
        }
        if(flg == 2)
        {
            cin>>x>>y>>k;
            update2(x,y,1,n,k,1);
        }
        else if(flg == 3)
        {
            cin>>x>>y;
            cout<<(long long)query(x,y,1,n,1)<<endl;
        }
    }
    return 0;
}