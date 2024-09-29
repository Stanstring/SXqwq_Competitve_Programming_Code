#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 100;
size_t n,m;
size_t f[(1<<18)+10][N][2];
size_t a[N];
size_t cnt;
bool vis[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    f[0][0][0] = 1;
    while(n)
    {
        a[cnt++] = n % 10;
        n /= 10;
    }
 //   cout<<cnt<<endl;
    for(size_t i = 0;i<(1<<cnt);i++)
    {
        memset(vis,0,sizeof(vis));
        for(int j=0;j<cnt;j++)
        {
            if(i&(1<<j)||vis[a[j]]) continue;
            vis[a[j]] = 1;
            for(int k=0;k<m;k++)
            {
                if(a[j])
                {
                    f[i|(1<<j)][(k*10+a[j])%m][1] += f[i][k][0];
                    f[i|(1<<j)][(k*10+a[j])%m][1] += f[i][k][1];
                }
                else f[i|(1<<j)][(k*10+a[j])%m][1] += f[i][k][1];
            }
        }
    }
    cout<<f[(1<<cnt)-1][0][1]<<endl;
    return 0;
}