#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
constexpr int N = 1000010;
constexpr int MAXN = 1ll;
size_t l,r;
size_t ans1[N],ans2[N],f[N],minn[N],a[N];
void solve(size_t n,size_t *ans)
{
    size_t tmp = n;
    size_t cnt = 0;
    while(n)
    {
        a[++cnt] = n%10;
        n/=10;
    }
    for(size_t i = cnt;i >= 1;i--)
    {
        for(size_t j=0;j<10;j++) ans[j] += f[i-1]*a[i];
        for(size_t j=0;j<a[i];j++) ans[j] += minn[i-1];
        tmp -= minn[i-1]*a[i];
        ans[a[i]] += tmp+1;
        ans[0] -= minn[i-1];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>l>>r;
    minn[0] = MAXN;
    for(int i=1;i<=13;i++) 
    {
        f[i] = f[i-1] * 10 + minn[i-1];
        minn[i] = 10ll*minn[i-1];
    }
    solve(r,ans1);
    solve(l-1,ans2);
    for(int i=0;i<10;i++) cout<<ans1[i]-ans2[i]<<" ";
    cout<<endl;
    return 0;
}