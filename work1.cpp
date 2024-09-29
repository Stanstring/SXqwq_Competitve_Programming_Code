#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 10000010;
int n,T;
struct Node
{
    int t,p;
}qwq[N];
bool cmp(Node a,Node b){return a.p > b.p;}
signed main()
{
    freopen("ex_work3.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>T;
 //   cout<<n<<" "<<T<<endl;
    for(int i=1;i<=n;i++)
        cin>>qwq[i].t;
    for(int i=1;i<=n;i++) cin>>qwq[i].p;
    sort(qwq+1,qwq+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(qwq[j].p*(j-1)+qwq[j].t < qwq[i].p*(i-1)+qwq[i].t) swap(qwq[i],qwq[j]);
        }
    }
    int cnt = 0;
     for(int j=1;j<=n;j++)
        {
            T -= qwq[j].t;
            T -= qwq[j].p*(j-1);
            if(T >= 0) cnt ++;
            else break;
        }
    cout<<cnt<<endl;
    return 0;
}