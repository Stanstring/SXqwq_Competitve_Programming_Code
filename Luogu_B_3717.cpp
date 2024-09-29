#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int mod = 998244353;
constexpr int N = 10000010;
int f[N],inv[N];
int T,n;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    T = read();
    n = read();
    f[0] = f[1] = inv[0] = inv[1] = 1;
    for(int i=2;i<=n;i++) f[i] = f[i-1]*i%mod,inv[i] = (mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=n;i++) inv[i] = inv[i-1]*inv[i]%mod;
    int ans = 0;
    while(T--)
    {
        int nn,mm;
        cin>>nn>>mm;
        ans ^= f[nn]*inv[mm]%mod*inv[nn-mm]%mod;
    }
  write(ans);
    return 0;
}