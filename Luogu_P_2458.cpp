#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int INF = 0x3f3f3f3f;
const int N = 500010;
size_t n;
size_t f[N][5];
size_t val[N];
vector <int> Edge[N];
void dfs(int u,int fat)
{
    f[u][0] = val[u];
    f[u][2] = INF;
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        dfs(v,u);
        f[u][0] += min({f[v][0],f[v][1],f[v][2]});
        f[u][1] += min(f[v][0],f[v][2]);
    }
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        f[u][2] = min(f[u][2],f[u][1]-min(f[v][0],f[v][2])+f[v][0]);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(size_t i=1;i<=n;i++)
    {
        size_t u,w,son_num,v;
        cin>>u>>w>>son_num;
        val[u] = w;
        for(size_t j=1;j<=son_num;j++)
        {
            cin>>v;
            Edge[u].push_back(v);
            Edge[v].push_back(u);
        } 
    }
    dfs(1,0);
    cout<<min(f[1][0],f[1][2])<<endl;
    return 0;
}