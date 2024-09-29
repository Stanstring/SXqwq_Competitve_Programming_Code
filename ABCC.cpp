#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    int n;
    int a[N],b[N];
    void solve()
    {
        int maxn1 = -INF,maxn2 = -INF;
        cin>>n;
        for(int i=1;i<=n;i++) 
        {
            int t;
            cin>>t;
            maxn1 = max(maxn1,t);
        }
        for(int i=1;i<=n;i++)
        {
            int t;
            cin>>t;
            maxn2 = max(maxn2,t);
        }
        cout<<maxn1 + maxn2<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}