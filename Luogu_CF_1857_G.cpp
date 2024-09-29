#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
const int mod = 998244353;
int n,s;
int ans;
int fa[N],siz[N];
struct Node
{
    int u,v,w;
    bool operator<(const Node &a)const{
        return w < a.w;
    }
}Edge[N];
int T;
long long fpow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans*=a;
		b>>=1;
		a*=a;
        a %= mod;
        ans %= mod;
	} 
	return ans;
}
void init()
{
    for(int i=1;i<=n;i++) fa[i] = i,siz[i] = 1;
}
int find(int x)
{
    if(fa[x] == x) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void kruskal()
{
    for(int i=1;i<n;i++)
    {
        int ii = find(Edge[i].u),jj = find(Edge[i].v);
        ans = (ans*fpow(s-Edge[i].w+1,siz[ii]*siz[jj]-1)%mod)%mod;
        fa[ii] = jj;
        siz[jj] += siz[ii];
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
    {
        cin>>n>>s;
        init();
        for(int i=1;i<n;i++) cin>>Edge[i].u>>Edge[i].v>>Edge[i].w;
        sort(Edge+1,Edge+n);
       ans = 1;
        kruskal();
        cout<<ans%mod<<endl;
    }
}