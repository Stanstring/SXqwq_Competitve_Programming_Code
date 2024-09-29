#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5;
namespace solution
{
    typedef pair<int,int> PAIR;
    int fa[N];
    bool flg[N];
    int val[N];
    int T,sub;
    int n,m;
    int ans = 0;
    bool vis[N];
    int f[N];
    vector <PAIR> Edge[N];
    vector <int> edge[N];
    int sum = 0;
    int get_siz(int u=n+2)
    {
        vis[u] = 1;
        int siz = 1;
        for(auto t:Edge[u])
        {
            int v = t.first,w = t.second;
            if(vis[v])
            {
                if(f[v] != (f[u]^w)) sum = 0;
            }
            else 
            {
                f[v] = f[u]^w;
                siz += get_siz(v);
            }
        }
        return siz;
    }
    int get(int u=n+2)
    {
        int siz = 1;
        for(auto t:edge[u])
            siz += get(t);
        return siz;
    }
    void init(){for(int i=1;i<=n*2;i++) {fa[i] = i;flg[i] = 0;}}
    void memset1()
    {
        memset(val,0,sizeof(val));
        memset(vis,0,sizeof(vis));
        memset(Edge,0,sizeof(Edge));
        memset(edge,0,sizeof(edge));
    //    Edge->clear();
      //  edge->clear();
        memset(f,0,sizeof(f));
        ans = 0;
        sum = 0;
    }
    void solve()
    {
        cin>>n>>m;
        memset1();
        int T = n+1,U = n+2;
        init();
        while(m--)
        {
            char op;
            int x,y;
            cin>>op;
            if(op == 'T' || op == 'F' || op == 'U')
            {
                cin>>x;
                if(op == 'T') {fa[x] = T;flg[x] = 0;}
                else if(op == 'F'){fa[x] = T;flg[x] = 1;}
                else {fa[x] = U;flg[x] = 0;}
            }
            else if(op == '+')
            {
                cin>>x>>y;
                fa[x] = fa[y];
                flg[x] = flg[y];
            }
            else if(op == '-')
            {
                cin>>x>>y;
                fa[x] = fa[y];
                flg[x] = (!flg[y]);
            }
        }
        for(int i=1;i<=n;i++)
        {
            Edge[fa[i]].push_back(PAIR(i,flg[i]));
            Edge[i].push_back(PAIR(fa[i],flg[i]));
        }
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]) 
            {
                sum = 1;f[i] = 1;
                int t = get_siz(i);
                if(!sum) ans += t;
            }
        }
        for(int i=1;i<=n;i++) edge[fa[i]].push_back(i);
        ans += get()-1;
        cout<<ans<<endl;
        return;
    }
    void mian()
    {
        cin>>sub>>T;
        while(T--) {solve();}
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
}