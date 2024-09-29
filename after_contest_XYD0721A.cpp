#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
size_t n;
vector <size_t> Edge[N];
size_t l[N],r[N];
size_t c[N];
size_t ans;
void dfs(size_t u)
{
    c[u] = 0;
    for(auto v:Edge[u]) 
    {
        dfs(v);
        c[u] += c[v];
    }
    if(c[u] < l[u]) 
    {
        ans ++;
        c[u] = r[u];
    }
    else if(c[u] > r[u]) 
    {
        c[u] = min(c[u],r[u]);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(size_t i=2;i<=n;i++) 
    {
        size_t v;
        cin>>v;
        Edge[v].push_back(i);
    }
    for(size_t i = 1;i<=n;i++) cin>>l[i]>>r[i];
    dfs(1);
    cout<<ans<<endl;
    return 0;
}