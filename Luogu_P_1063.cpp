#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1010;
namespace solution
{
    int n;
    int a[N],b[N];
    int f[N][N];
    void solve()
    {
        cin>>n;
        for(int i=1;i<=n;i++) {cin>>a[i],a[i+n] = a[i];}
        for(int i=1;i<=2*n-1;i++) b[i] = a[i+1];
     //   n *= 2;
        b[2*n] = a[1];
     int maxn = 0;
        for(int len = 1;len < n;len ++)
        {
            for(int l = 1;l<=n*2-len;l++)
            {
                int r = l+len;
                //if(r > n*2) break;
                for(int k=l;k<=r-1;k++)
                {
                    f[l][r] = max(f[l][r],f[l][k]+f[k+1][r]+a[l]*b[k]*b[r]);
                }
          //      maxn = max(maxn,f[l][r]);
            }
        }
        for(int i=1;i<=n;i++) maxn = max(maxn,f[i][i+n-1]);
        cout<<maxn<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}