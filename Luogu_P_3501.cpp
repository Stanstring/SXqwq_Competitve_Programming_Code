#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define ull unsigned long long
#define size_t unsigned long long
using namespace std;
using namespace __gnu_pbds;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 8000010;
int p = 13331;
size_t n;
char s[N],t[N];
size_t pp[N];
size_t f[N],g[N];
int ans = 0;
void solve(size_t x)
{
    int l = 0,r = min(x,n-x);
    while(l < r)
    {
     //   cout<<l<<" "<<r<<endl;
        int mid = (l+r+1)>>1;
       if((ull)(f[x]-f[x-mid]*pp[mid])==(ull)(g[x+1]-g[x+1+mid]*pp[mid])) l = mid;
        else r = mid - 1;
    }
    ans += l;
}
signed main()
{
    cin>>n;
    scanf("%s",s+1);
    pp[0] = 1;
     for(int i=1;i<=n;i++) pp[i] = pp[i-1]*p;
    for(int i=1;i<=n;i++)
    {
        if(s[i] == '1') t[i] = '0';
        else t[i] = '1';
    }
    for(int i=1;i<=n;i++) f[i] = f[i-1]*p+(s[i]-'0');
    for(int i=n;i>=1;i--) g[i] = g[i+1]*p+(t[i]-'0');
    for(int i=1;i<n;i++)
    {
        if(s[i] == s[i+1]) continue;
        solve(i);
    }
    cout<<ans<<endl;
    return 0;
}