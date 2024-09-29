#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
int T;
namespace solution
{
    #define Impossible cout<<"Impossible!"<<endl;return;
    int n,m,cnt = 0;
    vector <int> Edge[N];
    priority_queue <int> q;
    int in[N];
    int ans[N];
    void topsort()
    {
        while(!q.empty())
        {
            int p = q.top();
            ans[++cnt] = p;
            q.pop();
            for(auto v:Edge[p])
                if(!(--in[v])) q.push(v);
        }
    }
    void memset1()
    {
        fill(ans+1,ans+n+1,0);
        for(int i=1;i<=n;i++) Edge[i].clear();
        cnt = 0;
        fill(in+1,in+n+1,0);
    }
    void solve()
    {
        cin>>n>>m;
        memset1();
        bool no_answer = 0;
        for(int i=1;i<=m;i++)
        {
            int x,y;
            cin>>x>>y;
            if(x == y) no_answer = 1;
            Edge[y].push_back(x);
            in[x] ++;
        }
        if(no_answer) {Impossible}
        for(int i=1;i<=n;i++)  if(!in[i]) q.push(i);
        topsort();
        if(cnt < n) {Impossible}
        for(int i=n;i>=1;i--) cout<<ans[i]<<" ";
        cout<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
        solution::solve();
    return 0;
}