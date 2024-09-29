#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
int n,k;
int a[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    int ans = k;
    for(int i=1;i<=n;i++) ans = __gcd(ans,a[i]);
    cout<<k/ans<<endl;
    for(int i=0;i<k/ans;i++) cout<<i*ans<<" ";
    cout<<endl;
    return 0;
}