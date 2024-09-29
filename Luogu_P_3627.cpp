#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
int n,m;
int dfn[N],low[N];
stack <int> s;
int in_stack[N];
int cnt = 0;
int fa[N];
int sum[N];
int fa_cnt = 0;
int a[N];
int ans[N];
vector <int> Edge[N],new_Edge[N];
int in[N];
void tarjan(int pos)
{
    dfn[pos] = low[pos] = ++cnt;
    in_stack[pos] = 1;
    s.push(pos);
    for(int i=0;i<Edge[pos].size();i++)
    {
        int noww = Edge[pos][i];
        if(!dfn[noww])
        {
            tarjan(noww);
            low[pos] = min(low[pos],low[noww]);
        }
        else if(in_stack[noww])
        {
            low[pos] = min(low[pos],dfn[noww]);
        }
    }
    if(dfn[pos] == low[pos])
    {
        fa_cnt ++;
        while(s.top() != pos)
        {
            sum[fa_cnt] += a[s.top()];
            fa[s.top()] = fa_cnt;
            in_stack[s.top()] = 0;
            s.pop();
        }
        s.pop();
        sum[fa_cnt] += a[pos];
        fa[pos] = fa_cnt;
        in_stack[pos] = 0;
    }
}
void topsort(int s)
{
    queue <int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
      //  cout<<u<<endl;
        q.pop();
        for(auto v:new_Edge[u])
        {
            ans[v] = max(ans[v],ans[u] + sum[v]);
            if(!(--in[v])) q.push(v);
        }
    }
}
signed main()
{
    freopen("P3627_3.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        Edge[u].push_back(v);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    int s,p;
    cin>>s>>p;
    tarjan(s);
  //  tarjan(s);
    for(int i=1;i<=n;i++)
    {
        if(!fa[i]) 
        {
           // cout<<"qwq"<<endl;
            continue;
        }
       for(int j=0;j<Edge[i].size();j++)
       {
            if(!fa[Edge[i][j]]) continue;
            if(fa[i] != fa[Edge[i][j]]) 
            {
              //  cout<<"qwq"<<endl;
                bool can_push = true;
                for(int k=0;k<new_Edge[fa[i]].size();k++)
                {
                    if(new_Edge[fa[i]][k] == fa[Edge[i][j]]) 
                    {
                        can_push = false;
                        break;
                    }
                }
                if(can_push)
                {
                 //   cout<<fa[i]<<" "<<fa[Edge[i][j]]<<endl;
                    //new_Edge[fa[Edge[i][j]]].push_back(fa[i]);
                    new_Edge[fa[i]].push_back(fa[Edge[i][j]]);
                    in[fa[Edge[i][j]]] ++;
                }
            }
       }
    }
  //  cout<<in[fa[s]]<<endl;
    ans[fa[s]] = sum[fa[s]];
    for(int i=1;i<=fa_cnt;i++) ans[i] = sum[i];
    topsort(fa[s]);
    vector <int> d;
    d.clear();
    for(int i=1;i<=p;i++)
    {
        int t;
        cin>>t;
        d.push_back(t);
    }
    int maxn = 0;
    for(auto t:d)
    {
        if(!fa[t]) continue;
        maxn = max(maxn,ans[fa[t]]);
    }
    cout<<maxn<<endl;
    return 0;
}