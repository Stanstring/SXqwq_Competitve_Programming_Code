#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
int n,q;
int f[N][50];
int depth[N];
int minn[N],dfn[N],a[N];
int cnt = 0;
int root;
vector <int> Edge[N];
int vis[N];
priority_queue<int,vector<int>,greater<int> > qq;
bool cmp(int a,int b){return minn[a] < minn[b];}
void dfs1(int u)
{
    minn[u] = u;
    depth[u] = depth[f[u][0]] + 1;
    for(int i=1;i<=20;i++) f[u][i] = f[f[u][i-1]][i-1];
    for(auto v:Edge[u])
    {
        dfs1(v);
        minn[u] = min(minn[u],minn[v]);
    }
}
void dfs2(int u)
{
    for(auto v:Edge[u])
        dfs2(v);
    dfn[u] = ++cnt;
    a[cnt] = u;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>f[i][0];
        if(!f[i][0]) root = i;
        else Edge[f[i][0]].push_back(i);
    }
    dfs1(root);
    for(int i=1;i<=n;i++) sort(Edge[i].begin(),Edge[i].end(),cmp);
    dfs2(root);
    for(int i=1;i<=n;i++) qq.push(i);
    while(q--)
    {
        int op,x;
        cin>>op>>x;
        if(op == 1)
        {
            int res = 0;
            for(int i=1;i<=x;i++) 
            {
                res = qq.top();
                qq.pop();
                vis[a[res]] = 1;
            }
            cout<<a[res]<<endl;
        }
        else
        {
            int res = 0,p = x;
            for(int i = 20;i>=0;i--)
            {
                if(vis[f[p][i]]) p = f[p][i];
            }
            vis[p] =0;
            qq.push(dfn[p]);
            cout<<depth[x] - depth[p]<<endl;
        }
    }
    return 0;
}