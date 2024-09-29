#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 100010;
int n;
int a[N];
int maxn = -1;int qwq[N];
bool check(int l,int r)
{
    
    fill(qwq+1,qwq+n+1,0);
    for(int i=l;i<=r;i++)
    {
        qwq[a[i]] ++;
        if(qwq[a[i]] > 2) return 0;
    }
    for(int i=l;i<=r;i++) if(qwq[a[i]] != 2) return 0;
    return 1;
}
signed main()
{
 //   freopen("input.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    int ans = 0;
    int maxn = 0;
    for(int i=1;i<=n;i++) cin>>a[i],maxn = max(maxn,a[i]);
    for(int i=1;i<=n;i++)
    {
        memset(qwq,0,sizeof(qwq));
        qwq[a[i]] ++;
        int number = 0,ok = 0;number ++;
        for(int j=i+1;j<=n;j++) 
        {
            //cout<<number<<" "<<ok<<endl;
          //  cout<<qwq[a[j]]<<endl;
            if(number == ok && number && ok) {ans ++;}
             if(!qwq[a[j]]) number ++;
            qwq[a[j]] ++;
            if(qwq[a[j]] > 2) break;
            if(qwq[a[j]] == 2) ok ++;
        }
    }
    cout<<ans<<endl;
    return 0;
}