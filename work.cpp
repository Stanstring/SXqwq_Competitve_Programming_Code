#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 1e11;
int n,T;
struct Node
{
    int t,p;
}qwq[N];
int countt = 0;
int vis[N];
int minn = INF,minx;
bool cmp(Node a,Node b){return a.p/a.t*a.t > b.p/b.t*b.t;}
signed main()
{
   freopen("ex_work3.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>T;
   // cout<<n<<" "<<T<<endl;
    for(int i=1;i<=n;i++) 
    {
        int t;
        cin>>t;
        if(t > T) 
        {
            vis[i] = 1;
            continue;
        }
        qwq[++countt].t = t;
    }
    countt = 0;
    for(int i=1;i<=n;i++) 
    {
        int p;
        cin>>p;
        if(vis[i]) continue;
        qwq[++countt].p = p;
    }
    int cnt = 0;
    int maxn = 0;
 //   cout<<countt<<endl;
    int TT = T;
    for(int i=1;i<=200000;i++)
    {
        cnt = 0;
        T = TT;
        //cout<<T<<endl;
        random_shuffle(qwq+1,qwq+countt+1);
        for(int j=1;j<=countt;j++)
        {
         //   cout<<qwq[j].t<<endl;
            T -= qwq[j].t;
         //   cout<<T<<endl;
            T -= qwq[j].p*(j-1);
            if(T >= 0) cnt ++;
            else break;
        }
        maxn = max(maxn,cnt);
   // cout<<cnt<<endl;
    }
    cout<<maxn<<endl;
    return 0;
}