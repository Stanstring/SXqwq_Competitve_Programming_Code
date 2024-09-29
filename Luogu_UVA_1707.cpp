#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 10000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    #define x first
    #define y second
    typedef pair<int,int> PAIR;
    PAIR p[N];
    int f[50][N];
    int n,k;
    void memset1()
    {
        memset(p,0,sizeof(p));
     //   n = 0;
       // k = 0;
    }
    void solve()
    {
      
        while(cin>>n>>k)
        {
         //   memset1();
                 //   if(!n && !k) exit(0);
        for(int i=1;i<=k;i++)
        {
            int l,r;
            cin>>l>>r;
            if(l > r) r += n;
            p[i] = {l,r};
        }
        sort(p+1,p+1+k);
        int r = 0;
        for(int i=1,j=1,maxn = 0;i<=n*2;i++)
        {
            while(j <= k && p[j].x <= i) 
            {
                r = max(r,p[j].y+1);
                j++; 
            }

            f[0][i] = r;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j<=(n*2);j++) f[i][j] = f[i-1][f[i-1][j]];
        int ans = INF;
        for(int i=1;i<=n;i++)
        {
            int x = i,sum = 0;
            for(int j=20;j>=0;j--)
            {
               if(f[j][x] < i+n) 
               {
                    x = f[j][x];
                    sum += (1<<j);
               }
            }
            x = f[0][x];
            sum ++;
            if(x >= i+n) ans = min(ans,sum);
        }
        if(ans == INF) cout<<"impossible"<<endl;
        else cout<<ans<<endl;
     //   return;
        }

    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //while(1)
   // {
        solution::solve();
   // }
}