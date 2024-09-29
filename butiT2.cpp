#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 10010;
int n,m,ans;
int solve(vector <int> &a)
{
    int len = a.size();
    int f[N][2];
    f[0][0] = f[0][1] = 0;
    //memset(f,0,sizeof(f));
    for(int i=1;i<len;i++) 
    {
        f[i][1] = f[i-1][0] + max(0,a[i-1]+a[i]);
        f[i][0] = max(f[i-1][0],f[i-1][1]);
    }
    return max(f[len-1][0],f[len-1][1]);
}
int main()
{
    freopne("tunnel.in","r",stdin);
    freopen("tunnel.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    vector <vector <int> >col(m),row(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int t;
            cin>>t;
            col[j].push_back(t);
            row[i].push_back(t);
        }
    }
    int ans = 0 ;
    for(auto &v:row) ans += solve(v);
    for(auto &v:col) ans += solve(v);
    cout<<ans<<endl;
    return 0;
}