#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 3030;
constexpr int mod = 1e9+7;
namespace solution
{
    int c[N][N];
    int n,m;
    int sum = 0;
    int ans = 0;
    int a[N];
    int t;
    void solve()
    {
        cin>>t;
	    c[0][0]=1;
	    for(int i=1; i<=1005; i++)
	    {
		    c[i][0]=c[i][i]=1;
		    for(int j=1; j<i; j++)
			    c[i][j]=c[i-1][j-1]+c[i-1][j],c[i][j]%=mod;
	    }
	    while(t--)
	    {
		    cin>>n>>m;
		    ans=1,sum=0;
		    for(int i=1; i<=m; i++)
			    cin>>a[i],sum+=a[i];
		    for(int i=1; i<=m; i++)
			    ans*=c[sum][a[i]],ans%=mod,sum-=a[i];
		    cout<<ans<<endl;
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