#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 8000010;
int n,q;
int maxn = 0;
int a[N];
stack <int> s;
int nxt[N][40];
int f[N][40];
int ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    maxn = log2(n) + 1;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        while(s.size() && a[s.top()] < a[i])
        {
            nxt[s.top()][0] = i;
            s.pop();
        } 
        s.push(i);
    }
    while(s.size()) {nxt[s.top()][0] = n+2;s.pop();}
    nxt[n+1][0] = nxt[n+2][0] = n+2;
    for(int i=1;i<=n;i++)
        f[i][0] = 1LL*a[i]*(nxt[i][0]-i);
    for(int i=1;i<=maxn;i++)
    {
        for(int j=1;j<=n+2;j++)
            nxt[j][i] = n+2;  
              for(int j=1;j+(1<<i)-1<=n;j++)
    {
        nxt[j][i] = nxt[nxt[j][i-1]][i-1];
        f[j][i] = f[j][i-1] + f[nxt[j][i-1]][i-1];
    }
    }
        

    while(q--)
    {
        int u,v;
        cin>>u>>v;
        int qwq = 1+(u^ans)%n,qaq = (v^(ans+1))%(n-qwq+1)+qwq;
        int pos = qwq;
        ans = 0;
        for(int i=maxn;i>=0;i--)
        {
            if(nxt[pos][i]-1 > qaq) continue;
            ans += f[pos][i];
            pos = nxt[pos][i];
        }
        ans += a[pos]*(qaq-pos+1);
        cout<<ans<<endl;
    }
    return 0;
}