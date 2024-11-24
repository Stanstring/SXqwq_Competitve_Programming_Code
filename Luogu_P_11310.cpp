#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace solution
{
    void solve()
    {
        int n,tot = 1;
        cin>>n;
        if(!n) {cout<<"NO!\n";return;}
        while(n % 2 != 1){tot ++;n/=2;}
        cout<<tot<<"\n";
    }
    void mian()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}