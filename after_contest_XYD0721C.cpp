#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 10000010;
constexpr int mod = 19260817;
int n;
int inv[N];
int a[N];
int maxn = 0;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);   
    cin>>n;
    for(int i=0;i<n;i++) 
    {
        int t;
        cin>>t;
        a[t] = 1;
        maxn = max(maxn,t);
    }
    inv[1] = 1;
    for(int i=2;i<=maxn;i++) inv[i] = (mod-mod/i)*inv[mod%i]%mod;
    int ans = 0;
    int val = maxn;
    for(int i=maxn;i>=1;i--) 
    {
        if(a[i]) val = i;
        ans = (ans+inv[maxn-i+1]*val)%mod;
    }
    cout<<ans<<endl;
    return 0;
}