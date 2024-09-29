#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
constexpr int mod = 1e9+7;
constexpr int INF = 998244353;
int n;
int a[N];
int g[N],f[N];
long long qpow(long long a,long long b){
	long long sum=1;
	while(b){
		if(b&1)//与运算，可判断奇偶，详细见注释
		sum=sum*a%mod;//取模运算
		a=a*a%mod;
		b>>=1;//位运算，右移，相当于除以2
	}
	return sum;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int ans = 0;
    g[0] = 1;
    for(int i=1;i<=n;i++) g[i] = g[i-1]*a[i] % mod;
    f[n] = qpow(g[n],mod-2);
    for(int i=n;i>=0;i--) f[i-1] = f[i]*a[i]%mod;
    for(int i=1;i<=n;i++) 
    {
        ans *= INF;
        ans %= mod;
        ans += (f[i]*g[i-1]);
        ans %= mod;
    }
    cout<<ans<<endl;
}   