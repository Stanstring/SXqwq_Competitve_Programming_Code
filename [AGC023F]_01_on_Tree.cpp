#include <bits/stdc++.h>
#include <bits/extc++.h>
#define x first 
#define y second
#define int long long
using namespace std;
constexpr int N = 5000010;
constexpr int INF = 1e18;
typedef pair<double,int> PAIR;
int n;
int fa[N];
int f[N];
int a[N],cnt1[N],cnt0[N];
int vis[N];
priority_queue<PAIR,vector<PAIR>,greater<PAIR> > q;
int ans = 0;
int find(int x)
{
    if(x == f[x]) return x;
    f[x] = find(f[x]);
    return f[x];
}
void merge(int x,int y)
{
    int i = find(x),j = find(y);
    if(i == j) return;
    ans += cnt1[y]*cnt0[x];
    cnt1[y] += cnt1[x];
    cnt0[y] += cnt0[x];
    f[i] = j; 
}
void solve()
{
    while(!q.empty())
    {
        auto t = q.top();
        q.pop();
        int u = t.y;
        if(vis[u]) continue;
        vis[u] = 1;
        if(fa[u] != -1) 
        {
            int x = find(fa[u]);
            merge(u,x);
            q.push(PAIR((cnt0[x]==0?INF:1.0*cnt1[x]/(1.0*cnt0[x])),x));
        }
    }
    cout<<ans<<endl;
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    fa[0] = -1;
    for(int i=1;i<n;i++) 
    {
        cin>>fa[i];
        --fa[i];
    }
    for(int i=0;i<n;i++) 
    {
        f[i] = i;
        cin>>a[i];
        if(a[i]) ++cnt1[i];
        else ++cnt0[i];
        q.push(PAIR((cnt0[i]==0?INF:1.0*cnt1[i]/(1.0*cnt0[i])),i));
	}
    solve();
}
