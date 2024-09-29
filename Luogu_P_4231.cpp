#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 10000010;
namespace solution
{
    int n,m;
    int a[N],b[N];
    void solve()
    {
        cin>>n>>m;
        while(m--)
        {
            int l,r,s,e;
            cin>>l>>r>>s>>e;
            int gc = (e-s)/(r-l);
            a[l] += s;
            a[l+1] += (gc-s);
            a[r+1] += (-e-gc);
            a[r+2] += e;
        }
        for(int i=1;i<=n;i++) a[i] += a[i-1];
        int maxn = 0;
        int ans = 0;
        int sum = 0;
        for(int i=1;i<=n;i++)
        {
            sum += a[i];
            ans ^= sum;
            maxn = max(maxn,sum);
        }
        cout<<ans<<" "<<maxn<<endl;
        return;
    }
}
signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}