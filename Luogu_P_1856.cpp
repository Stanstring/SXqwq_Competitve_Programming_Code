#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 10010;
namespace solution
{
    int n;
    int ans1 = 0,ans2 = 0;
    struct LINE
    {
        int lx,ly,rx,ry;
    }line[N];
    bool cmpx(LINE a,LINE b){return a.lx < b.lx;}
    bool cmpy(LINE a,LINE b){return a.ly < b.ly;}
    void solve_x()
    {
        int h[N];
        memset(h,-1,sizeof(h));
        sort(line+1,line+n+1,cmpx);
        for(int i=1;i<=n;i++)
        {
            for(int j=line[i].ly;j < line[i].ry;j ++)
            {
                if(h[j] < line[i].lx) ans1 += 2;
                if(h[j] < line[i].rx) h[j] = line[i].rx;
            }
        }
    }
    void solve_y()
    {
        int h[N];
        memset(h,-1,sizeof(h));
        sort(line+1,line+n+1,cmpy);
        for(int i=1;i<=n;i++)
        {
            for(int j=line[i].lx;j < line[i].rx;j ++)
            {
                if(h[j] < line[i].ly) ans2 += 2;
                if(h[j] < line[i].ry) h[j] = line[i].ry;
            }
        }
    }
    void solve()
    {
        cin>>n;
        for(int i=1;i<=n;i++) 
        {
            cin>>line[i].lx>>line[i].ly>>line[i].rx>>line[i].ry;
            line[i].lx += INF,line[i].ly += INF,line[i].rx += INF,line[i].ry += INF;
        } 
        solve_x();
        solve_y();
        cout<<ans1+ans2<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}