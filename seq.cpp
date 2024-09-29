#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 10000010;
int n,m;
int a[N];
bool flg[N];
int q[N];
int cnt = 0;
signed main()
{
   freopen("ex_seq2.in","r",stdin);
   freopen("output.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        flg[a[i]] = 1;
   }
    for(int i=1;i<=n;i++)
        if(!flg[i]) q[++cnt] = i;
    int mem = cnt;
    cnt = 1;
    for(int i=1;i<=m;i++)
    {
        while(q[cnt] < a[i] && cnt <= mem) 
        {
            cout<<q[cnt]<<endl;
            cnt ++;
        }
        cout<<a[i]<<endl;
    }
    while(cnt <= mem)
    {
    //    if(!q[cnt]) return 0;
        cout<<q[cnt]<<endl;
        cnt ++;
    }
}