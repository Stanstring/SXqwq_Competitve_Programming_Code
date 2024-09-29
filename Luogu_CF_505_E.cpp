#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int >PAIR;
constexpr int N = 1000010;
int n,m,k,p;
int h[N],a[N],c[N];
int l,r;
bool check(int x)
{
    priority_queue <PAIR> q;
    for(int i=1;i<=n;i++) 
    {
        if(h[i] + m*a[i] <= x) continue;
        q.push(PAIR(-(x/a[i]),i));
        c[i] = 0;
    }
    int count = 0;
    for(int i=1;q.size() && i <= m;i++)
    {
        for(int j=1;q.size() && j <= k ;j++)
        {
            if(-q.top().x < i) return 0;
            int t = q.top().y;
            q.pop();
            int w = (x + (++c[t])*p)/a[t];
            if(w < m) q.push(PAIR(-w,t));
            ++count;
        }
    }
    for(int i=1;i<=n;i++)
    {
        int w = x + c[i]*p-m*a[i];
        if(h[i] <= w) continue;
        w = (h[i]-w-1)/p+1;
        if(count + w > m*k) return 0;
        count += w;
    }
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>k>>p;
    for(int i=1;i<=n;i++) 
    {
        cin>>h[i]>>a[i];
        l = max(l,a[i]);
        r = max(r,h[i] + m*a[i]);
    }
    while (l<r)
    {
        int mid = (l+r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout<<l<<endl;
    return 0;
}