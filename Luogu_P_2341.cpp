#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 100010;
vector <int> Edge[N];
vector <int> new_edge[N];
int n,m;
int dfn[N],low[N];
int cnt = 0;
stack <int> s;
bool in_stack[N];
int fa_cnt = 0;
int sum[N];
int fa[N];
int in[N];
int out[N];
void Tarjan(int pos)
{
    dfn[pos] = low[pos] = ++cnt;
    in_stack[pos] = 1;
    s.push(pos);
    for(int i=0;i<Edge[pos].size();i++)
    {
        int noww = Edge[pos][i];
        if(!dfn[noww])
        {
            Tarjan(noww);
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
            sum[fa_cnt] ++;
            fa[s.top()] = fa_cnt;
            in_stack[s.top()] = 0;
            s.pop();
        }
        s.pop();
        sum[fa_cnt] ++;
        fa[pos] = fa_cnt;
        in_stack[pos] = 0;
    }
}

int main()
{
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
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
   for(int i=1;i<=n;i++)
    {
       for(int j=0;j<Edge[i].size();j++)
       {
            if(fa[i] != fa[Edge[i][j]]) 
            {
                bool can_push = true;
                for(int k=0;k<new_edge[fa[i]].size();k++)
                {
                    if(new_edge[fa[i]][k] == fa[Edge[i][j]]) 
                    {
                        can_push = false;
                        break;
                    }
                }
                if(can_push)
                {
                    new_edge[fa[i]].push_back(fa[Edge[i][j]]);
                    in[fa[Edge[i][j]]] ++;
                    out[fa[i]] ++;
                }   
            }
       }
    }
    int ans = 0;
    for(int i=1;i<=fa_cnt;i++)
    {
        if(!out[i])
        {
            if(!ans) ans = i;
            else 
            {
                cout<<"0"<<endl;
                exit(0);
            }
        }
    }
    cout<<sum[ans]<<endl;
    return 0;
}