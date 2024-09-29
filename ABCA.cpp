#include <bits/stdc++.h>
using namespace std;
namespace solution
{
    void solve()
    {
        int res = 0;
        for(int i=1;i<=12;i++)
        {
            string s;
            cin>>s;
            if(s.size() == i) res ++;
        }
        cout<<res<<endl;
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