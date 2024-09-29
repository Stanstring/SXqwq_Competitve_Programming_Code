#include <bits/stdc++.h>
#include <bits/extc++.h>
#define unsignsed long long size_t
#define int size_t
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
int n;
int a[N],cnt[N];

int s[N];
int w[N];
unordered_map <size_t,int> m;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    mt19937 mt(time(0));
   // mt19937 mt(chrono::system_clock().now().time_since_epoch().count());
    uniform_int_distribution<unsigned long long> ran(1,(unsigned long long)-1);
    
    for(int i=1;i<=n;i++) w[i] = ran(mt);
    for(int i=1;i<=n;i++) cin>>a[i],s[i] = s[i-1] ^ w[a[i]];
    size_t ans = 0;
    for(int l = 1,r = 1;r <= n;r ++)
    {
        cnt[a[r]] ++;
        m[s[r-1]] ++;
        while(cnt[a[r]] > 2)
        {
            cnt[a[l]] --;
            m[s[l-1]] --;
            l ++;
        }
        ans += m[s[r]];
       // cout<<m[s[r]]<<endl;
    }
    cout<<ans<<endl;
    return 0;
}