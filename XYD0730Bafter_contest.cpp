#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 10000010;
int n,m;
int a[N];
int p,q;
int sum1[N],sum2[N];
bool cmp(int a,int b){return a > b;}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) sum1[i] = sum1[i-1] + a[i];
    for(int i=1;i<=n;i++) 
        sum2[i] = sum2[i-1]+(n-i+1)*a[i];
    while(m--)
    {
        cin>>p>>q;
        int l = 1,r = min(p,n);
        while(l < r)
        {
            int mid = (l+r) >> 1;
            if(sum2[mid] + (sum1[mid]*(p-n)) >= q) r = mid;
            else l = mid + 1;
        }
        if(sum2[min(n,p)]+(sum1[min(n,p)]*(p-n)) < q) cout<<"-1"<<endl;
        else cout<<r<<endl;
    }

}