#include <bits/stdc++.h>
using namespace std;
constexpr int N = 10000010;
namespace solution
{
    int a[N];
    void solve()
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        int maxn = 0;
        for(int i=1;i<=n;i++)
        {
            double t = ceil((i-2)*1.0/2*1.0);
            double t1 = ceil(max((n-i-1),0)*1.0/2*1.0);
          //  cerr<<t<<" "<<t1<<endl;
            maxn = max(maxn,a[i]+int(t+t1+1));
        }
     //   cerr<<endl;
        cout<<maxn<<endl;
        return;
    }
    void mian()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}