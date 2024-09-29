#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1010;
constexpr int MAXN = 1000010;
constexpr int INF = 1e10+10;
struct Node
{
    int u,v,w;
};
int n,m,k;
Node Edge[MAXN];
bool cmp(Node a,Node b){return a.w < b.w;}
int vis[MAXN];
int f[N][N];
int a[MAXN];
int cnt = 0;
int d[MAXN];
void floyd()
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(k == i) continue;
            for(int j=1;j<=n;j++)
            {
                if(j == i || j == k) continue;
                f[i][j] = min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>k;
    memset(f,INF,sizeof(f));
    for(int i=1;i<=m;i++) 
    {
        int u,v,w;
        cin>>u>>v>>w;
        Edge[i] = {u,v,w};
    }
    sort(Edge+1,Edge+m+1,cmp);
    int count = 0;
    for(auto t:Edge)
    {
        int u = t.u,v = t.v,w = t.w;
        vis[u] = vis[v] = 1;
        count ++;
        if(count > k) break;
    }
    for(int i=1;i<=n;i++) a[i] = a[i-1] + vis[i];
    n = a[n]; 
    for(int i=1;i<=k;i++) 
    {
        f[a[Edge[i].u]][a[Edge[i].v]] = Edge[i].w;
        f[a[Edge[i].v]][a[Edge[i].u]] = Edge[i].w;

    }
    floyd();
    int sum = 0 ;
    memset(d,0,sizeof(d));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<i;j++) 
        {
            d[++sum] = f[i][j];
        }
    }
    sort(d+1,d+sum+1);
    cout<<d[k]<<endl;
    return 0;
}   