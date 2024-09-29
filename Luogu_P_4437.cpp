#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
size_t n;
int fa[N],a[N],w[N];
int siz[N];
struct Node
{
    int x,siz,w;
    bool operator<(const Node &a)const{
        return w*a.siz > siz*a.w;
    }
};
priority_queue <Node> q;
void init(){for(int i=0;i<=n;i++) fa[i] = i,siz[i] = 1;}
int find(int x)
{
    if(x ==fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int x,int y)
{
    int i = find(x),j = find(y);
    if(i == j) 
    {
        cout<<"-1"<<endl;
        exit(0);
    }
    fa[i] = fa[j];
}
void solve()
{
    int ans = 0;
    while(!q.empty())
    {
        Node p = q.top();
        q.pop();
        int u;
        if(siz[u = find(p.x)] != p.siz) continue;
        int t = find(a[u]);
        fa[u] = t;
        ans += siz[t]*w[u];
        siz[t] += siz[u];
        w[t] += w[u];
        if(t) q.push({t,siz[t],w[t]});
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
    init();
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        merge(i,a[i]);
    }  
    for(int i=1;i<=n;i++) 
    {
        cin>>w[i];
        q.push({i,1,w[i]});
    }
    init();
    solve();
    return 0;
}