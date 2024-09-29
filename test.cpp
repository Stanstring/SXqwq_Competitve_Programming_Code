#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    #define x first
    #define y second
    typedef pair<int,int> PAIR;
    PAIR p[N];
    int f[N][50];
    int n,k;
    void solve()
    {
        cin>>n>>k;
        for(int i=1;i<=k;i++)
        {
            int l,r;
            cin>>l>>r;
            if(l > r) r += n;
            p[i] = {l,r};
        }
        sort(p+1,p+1+k);
        for(int i=1,j=1,maxn = 0;i<=n*2;i++)
        {
          // maxn = 0;
            while(j <= k && p[j].x <= i) 
                if(p[maxn].y < p[j].y+1) maxn = j ++;
            f[0][i] = p[maxn].y + 1;
         //   cerr<<f[0][i]<<endl;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j<=(n*2);j++) f[i][j] = f[i-1][f[i-1][j]];
        int ans = INF;
        for(int i=1;i<=(n*2);i++)
        {
            int finish = i+n,res = 1,u = i;
            for(int j=20;j>=0;j--)
            {
                if(f[j][u]<finish)
                {
                    res += (1<<j);
                    u = f[j][u];
                }
                u = f[0][u];
             //   cout<<u<<endl;
                if(u >= finish) ans = min(ans,res);
            }
        }
        if(ans == INF) cout<<"impossible"<<endl;
        else cout<<ans<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}