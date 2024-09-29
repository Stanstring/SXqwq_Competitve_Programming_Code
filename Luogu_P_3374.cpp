#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
namespace solution
{
    constexpr int MAXN = 1000010;
    struct BIT
    {
        int tree[N];
        int lowbit(int k){return k&(-k);}
        void modify(int i,int x)
        {
            for(int pos = i;pos < MAXN;pos+=lowbit(pos))
                tree[pos] += x;
        }
        int query(int x)
        {
            int ans = 0;
            for(int pos = x;pos;pos -= lowbit(pos)) {ans += tree[pos];}
            return ans;
        }
    }bit;
    void solve()
    {
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) 
        {
            int t;
            cin>>t;
            bit.modify(i,t);
        }    
        while(m--)
        {
            int op,x,k;
            cin>>op>>x>>k;
            if(op == 1) bit.modify(x,k);
            else cout<<bit.query(k)-bit.query(x-1)<<endl;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}