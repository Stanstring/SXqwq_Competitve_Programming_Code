#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
int n;
unordered_map<int,int> m;
unordered_map<int,int>::iterator q;
signed main()
{
    freopen("input.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int t;
        cin>>t;
        q = m.find(t);
        if(q != m.end()) 
        {
            cout<<i-1<<endl;
            exit(0);
        }       
        m[t] = i;
    }
    cout<<n<<endl;
    return 0;
}