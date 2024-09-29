#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
int n,q;
int d[N],c[N],l[N];
stack <int> s;
vector <int> Edge[N];
int depth[N];
int f[N][20],g[N][20];
void dfs(int u,int fa)
{
    depth[u] = depth[fa] + 1;
    f[u][0] = fa;
    g[u][0] = c[fa];
    for(int i=1;(1<<i) <= depth[u];i++) 
    {
        f[u][i] = f[f[u][i-1]][i-1];
        g[u][i] = g[f[u][i-1]][i-1] + g[u][i-1];
    }
    for(auto v:Edge[u]) 
        dfs(v,u);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++) 
        cin>>d[i]>>c[i];
    d[n+1] = c[n+1] = INF;
    s.push(1);
    for(int i=2;i<=n+1;i++)
    {
        while(!s.empty() && d[i] > d[s.top()])
        {
            l[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    for(int i=1;i<=n;i++) Edge[l[i]].push_back(i);
    dfs(n+1,0);
    while(q--)
    {
        int r,v;
        cin>>r>>v;
        if(c[r] >= v) 
        {
            cout<<r<<endl;
            continue;
        }
        v -= c[r];
        int p = r;
        int ans = 0;
        for(int i = 20;i>=0;i--)
        {
            if(g[p][i] <= v && (1<<i)<=depth[p])
            {
                v -= g[p][i];
                p = f[p][i];
            }
            if(v ==0) ans = p;
        }
        if(ans == 0) ans = f[p][0];
        if(ans == n+1) cout<<"0"<<endl;
        else cout<<ans<<endl;
        }
}