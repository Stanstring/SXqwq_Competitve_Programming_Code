#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    constexpr int MAXN = 1000;
    constexpr int INF = 0x3f3f3f3f;
    int n,m;
    int v[N],c[N];
    bool cmp(int a,int b){return a>b;}
    bool check(int x)
    {
        int t[N];
        for(int i=1;i<=n;i++) t[i] = v[i]-c[i]*x;
        sort(t+1,t+n+1,cmp);
        int sum = 0; 
        for(int i=1;i<=m;i++) sum += t[i];
        return sum >= 0;
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++) {cin>>v[i];v[i]*=MAXN;}
        for(int i=1;i<=n;i++) {cin>>c[i];}
        int l = 1,r = 1e9;
        while(l <= r)
        {
            int mid = (l+r) >>1;
            if(check(mid)) l = mid + 1;
            else r = mid - 1;
        }
        printf("%.3lf\n",(double)(l*1.0/MAXN));
        return;
    }
}
signed main()
{
    solution::solve();
}