#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
namespace solution
{
    int n,m;
    struct DSU
    {
        int fa[N][20];
        void init(){for(int i=1;i<=n;i++) for(int j=1;j<=10;j++) fa[i][j] = i;}
        int find(int x,int num)
        {
            if(fa[x][num] == x) return x;
            fa[x][num] = find(fa[x][num],num);
            return fa[x][num];
        }
        void merge(int x,int y,int num)
        {
            int i = find(x,num),j = find(y,num);
            if(i == j) return;
            fa[i][num] = j; 
        }
    }dsu;
    void solve()
    {
        int ans = 0;
        cin>>n>>m;
        dsu.init();
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            for(int j=w;j<=10;j++)
                dsu.merge(u,v,j);
            ans += w;
        }
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            for(int j=1;j<=10;j++)
            {
                int p = dsu.find(u,j),q = dsu.find(v,j);
                if(p == q) {ans -= max(j-w,0);break;}
            }
            for(int j=w;j<=10;j++) dsu.merge(u,v,j);
            cout<<ans<<endl;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}