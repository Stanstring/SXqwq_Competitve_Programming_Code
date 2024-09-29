#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t int
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int N = 1000010;
struct Node
{
    int time,money;
}qwq[N];
size_t n;
size_t ans = 0;
bool cmp(Node a,Node b){return a.time < b.time;}
priority_queue<int,vector<int>,greater<int> > q;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>qwq[i].time>>qwq[i].money;
    sort(qwq+1,qwq+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(qwq[i].time <= q.size())
        {
            if(qwq[i].money > q.top())
            {
                ans -= q.top();
                q.pop();
                q.push(qwq[i].money);
                ans += qwq[i].money;
            }
        }
        else
        {
            q.push(qwq[i].money);
            ans += qwq[i].money;
        }
    }
    cout<<ans<<endl;
    return 0;
}