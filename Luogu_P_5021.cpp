#include <bits/stdc++.h>
#define int long long
#define set multiset
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 1e9;
namespace solution
{
    typedef pair<int,int> PAIR;
    int n,m;
    int p,res;
    vector <PAIR> Edge[N];
    int siz[N];
    int f[N];
    void dfs(int u,int fa)
    {
        #define x first
        #define y second
        set <int> s;
        for(auto t:Edge[u])
        {
            int v = t.x,w = t.y;
            if(v == fa) continue;
            dfs(v,u);
            if(f[v] + w >= p) res ++;
            else s.insert(f[v] + w);
        }
        while(!s.empty())
        {
            set <int>::iterator it = s.begin();
            s.erase(it);
            set <int>::iterator it1 = s.lower_bound(p-*it);
            if(it1 == s.end()) f[u] = max(f[u],*it);
            else {res ++;s.erase(it1);}
        }
    }
    bool check(int k)
    {
        p = k;
        res = 0;
        fill(f+1,f+n+1,0);
        dfs(1,0);
        return res >= m;
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            Edge[u].push_back(PAIR(v,w));
            Edge[v].push_back(PAIR(u,w));
        }
        int l=0,r = INF;
        int answer;
        while (l<=r)
        {
            int mid = (l+r) >> 1;
            if(check(mid)) {l = mid+1;answer = mid;}
            else r = mid - 1;
        }
        cout<<answer<<endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}