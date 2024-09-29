#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 100010;
int n,k1;
int tree[N];
int a[N];
void build(int l,int r,int p,int num)
{
    if(l == r)
    {
        tree[p] |= 1;
        return;
    }
    int mid = (l+r) >> 1;
    if(num <= mid) build(l,mid,p<<1,num);
    else build(mid+1,r,p<<1|1,num);
    tree[p] = tree[p<<1] + tree[p<<1|1];
}
int query(int l,int r,int p,int k)
{
    if(l == r) return l;
    int mid = (l+r) >> 1;
    if(k <= tree[p<<1]) return query(l,mid,p<<1,k);
    else return query(mid+1,r,p<<1|1,k-tree[p<<1]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k1;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        build(1,INF,1,a[i]);
    }
    int res = query(1,INF,1,k1);
    if(res == INF) cout<<"NO RESULT"<<endl;
    else cout<<query(1,INF,1,k1)<<endl;
    return 0;
}