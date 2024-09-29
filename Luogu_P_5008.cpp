#include <bits/stdc++.h>
#define debug cerr<<"qwq"<<endl;
#define int long long
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    int n,m,k;
    vector <int> Edge[N],edge[N];
    struct Node
    {
        int val;
        bool vis = 0;
        bool operator<(const Node& a)const{
            return a.val < val;
        }
    }qwq[N];
    int in[N];
    int scc_minn[N];
    struct SCC
    {
        int dfn[N],low[N];
        int cnt = 0,fa_cnt = 0,fa[N];
        stack <int> s;
        bool in_stack[N],vis[N];
        void tarjan(int u)
        {
            s.push(u);
            in_stack[u] = 1;
            vis[u] = 1;
            dfn[u] = low[u] = ++cnt;
            for(auto v:Edge[u])
            {
                if(u == v) continue;
                if(!dfn[v])
                {
                    tarjan(v);
                    low[u] = min(low[u],low[v]);
                }
                else if(in_stack[v])
                    low[u] = min(low[u],dfn[v]);
            }
            if(dfn[u] == low[u])
            {
                fa_cnt ++;
                int minn = INF,minx = -1;
                int siz = 0;
                while(s.top() != u)
                {
                    siz ++;
                    int p = s.top();
                    s.pop();
                    fa[p] = fa_cnt;
                    if(qwq[p].val < minn) 
                    {
                        minn = qwq[p].val;
                        minx = p;
                    }
                    in_stack[p] = 0;
                }
                s.pop();
                siz ++;
                if(qwq[u].val < minn){minn = qwq[u].val;minx = u;}
                fa[u] = fa_cnt;
                in_stack[u] = 0;
                  if(siz > 1)
                    scc_minn[fa_cnt] = minx;
            }       
        }
    }scc;
    void solve()
    {
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++) cin>>qwq[i].val,qwq[i].vis = 0;
        for(int i=1;i<=m;i++)
        {
            int u,v;
            cin>>u>>v;
            Edge[u].push_back(v);
            qwq[v].vis = 1;
        } 
        for(int i=1;i<=n;i++) if(!scc.dfn[i]) scc.tarjan(i);
        for(int u=1;u<=n;u++)
        {
            for(auto v:Edge[u])
            {
                if(scc.fa[u] != scc.fa[v] || u == v) in[scc.fa[v]] =1; 
            } 
        }
        for(int i=1;i<=scc.cnt;i++) 
            if(!in[i]) {qwq[scc_minn[i]].vis = 0;}
        sort(qwq+1,qwq+n+1);
        int sum = 0;
        for(int i=1;i<=n;i++) 
            if(qwq[i].vis && k){sum += qwq[i].val;k--;if(!k) break;}
        cout<<sum<<endl;
        return;
    }
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("P5008_8.in","r",stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}