#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int INF = 1e9+10;
int minn = INF;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) 
    {
        int l,r;
        cin>>l>>r;
        minn = min(minn,r-l+1);
    }
    cout<<minn<<endl;
    for(int i=1;i<=n;i++) cout<<i%minn<<" ";
    cout<<endl;
    return 0;
}