#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
typedef pair<int,int> PAIR;
int n;
int a[N];
struct Node
{
    int u,v,w,pos;
}Edge1[N];
vector <int> Edge[N];
int dfnl[N],dfnr[N];
int cnt = 0;
int fa[N];
int m;
int ans[N];
void init(){for(int i=1;i<=n;i++) fa[i] = i;}
int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void dfs(int u,int fat)
{
    bool flag = 1;
    dfnl[u] = INF;
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        flag= 0;
        dfs(v,u);
        dfnl[u] = min(dfnl[u],dfnl[v]);
        dfnr[u] = max(dfnr[u],dfnr[v]);
    }
    if(flag) dfnl[u] = dfnr[u] = ++cnt;
    Edge1[++m] = {dfnl[u],dfnr[u]+1,a[u],u};
}
int countt = 0;
bool cmp(Node aa,Node bb) {return aa.w < bb.w;}
int MST = 0;
void kruskal()
{
	init();
    sort(Edge1+1, Edge1+m+1, cmp);
	int sum = 0;
	for (int l = 1; l <= n;)
	{
		int r;
		for (r = l; r + 1 <= n && Edge1[r].w == Edge1[r+1].w; r++);
		for (int i = l; i <= r; i++) 
        {
			if (find(Edge1[i].u) != find(Edge1[i].v))
            {
                ans[Edge1[i].pos] = true;
                countt++;
            }
        }
		for (int i = l; i <= r; i++) 
		{
			int fu = find(Edge1[i].u), fv = find(Edge1[i].v);
			if (fu == fv) continue;
			fa[fu] = fv;
            MST += Edge1[i].w;
		}
		l = r + 1;
	}
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    dfs(1,0);
    kruskal();
    cout<<MST<<" "<<countt<<endl;
    for(int i=1;i<=n;i++)
    {
        if(ans[i]) cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}