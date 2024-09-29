#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f3f3f3f;
namespace solution
{
    int answer[N];
    #define x first
    #define y second
    typedef pair<int,int> PAIR;
    struct Node
    {
        int l,r,num;
        bool operator<(const Node& a)const{
            return l < a.l;
        }
    };
    Node p[N];
    int f[50][N];
    int n,m;
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            int l,r;
            cin>>l>>r;
            if(l > r) r += m;
            p[i] = {l,r,i};
        }
        sort(p+1,p+1+n);
        for(int i=1;i<=n;i++) p[i+n].l = p[i].l+m,p[i+n].r = p[i].r + m;;
        int r = 0;
        for(int i=1,j=1,maxn = 0;i<=n*2;i++)
        {
          // maxn = 0;
            while(j <= 2*n && p[j].l <= p[i].r) 
            {
               // if(p[maxn].y < p[j].y+1)
               // {
                    j++; 
               // }
            }

            f[0][i] = j-1;
         //   cerr<<f[0][i]<<endl;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j<=(n*2);j++) f[i][j] = f[i-1][f[i-1][j]];
     //   int ans = INF;
        for(int i=1;i<=n;i++)
        {
            int up = p[i].l+m,ans = 0,q = i;
            for(int j=20;j>=0;j--)
            {
                if(f[j][q] && p[f[j][q]].r < up) 
                {
                    ans += (1<<j);
                    q = f[j][q];
                }
            }
            answer[p[i].num] = ans + 2;
        }
        for(int i=1;i<=n;i++) cout<<answer[i]<<" ";
        cout<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}