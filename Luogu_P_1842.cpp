#include <bits/stdc++.h>
#include <bits/extc++.h>
#define x first 
#define y second
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> PAIR;
constexpr int N = 100010;
constexpr int INF = 0x3f3f3f3f;
int n;
PAIR qwq[N];
bool cmp(PAIR a,PAIR b){return a.x + a.y < b.x+b.y;}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>qwq[i].x>>qwq[i].y;
    sort(qwq+1,qwq+n+1,cmp);
    int sum = 0,ans = - INF;
    for(int i=1;i<=n;i++)
    {
        ans = max(ans,sum-qwq[i].y);
        sum += qwq[i].x;
    }
    cout<<ans<<endl;
    return 0;
}