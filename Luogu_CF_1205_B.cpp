#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1010;
constexpr int INF = 0x3f3f3f3f;
int n;
int a[N];
int f[N][N],g[N][N];
int ans = INF;
void floyd()
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(k == i) continue; 
            for(int j=1;j<=n;j++) 
            {
                if(i == j ||i == k) continue;
             //   cout<<ans<<endl;
                ans = min(ans,f[i][j] + g[i][k] + g[k][j]);
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);  
    cin>>n;

    for(int i=1;i<=n;i++)
    {
        if(i >= 128) break;
        cin>>a[i];
        if(!a[i])
        {
            n--;
            i--;
        }
    }    
    if(n >= 128) 
    {
        cout<<"3"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if((a[i] & a[j]) && (i != j)) 
                f[i][j] = g[i][j] = 1;
            else f[i][j] = g[i][j] = INF;
        }
    }
    floyd();
    if(ans == INF) cout<<"-1"<<endl;
    else cout<<ans<<endl;
    return 0;
}