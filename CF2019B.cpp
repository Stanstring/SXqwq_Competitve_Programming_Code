#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 10000010;
namespace solution
{
    int a[N];
    int ans[N];
    void solve()
    {
        int n,q;
        cin>>n>>q;
        fill(ans+1,ans+n+1,0);
        for(int i=1;i<=n;i++) cin>>a[i];
        int cnt = 0;
        for(int i=1;i<n;i++)
        {
            ans[(n-i)*(++cnt)+1] ++;
            ans[(n-i)*(cnt)] += (a[i+1]-a[i]-1);
            
        }
        for(int i=1;i<=q;i++) 
        {
            int k;
            cin>>k;
            cout<<ans[k]<<" ";
        }
        cout<<endl;
    }
    void mian()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}