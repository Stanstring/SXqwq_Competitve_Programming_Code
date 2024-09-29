#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 8000010;
int n;
int a[N];
int maxn = 0;
unordered_map<int,int> m;
unordered_map<int,int>::iterator q;
signed main()
{
  //freopen("uoj4.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    int maxl,maxr;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int l=1,r=1;r<=n;r++)
    {
        bool flag = 0;
        while(m[a[r]])
        {
            m[a[l]] =0;
            l ++;
        }
     //   if(flag) l++;
        m[a[r]] = 1;
        maxn = max(maxn,r-l+1);
    }
    cout<<maxn<<endl;
    return 0;
}