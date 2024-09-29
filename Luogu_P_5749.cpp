#include <bits/stdc++.h>
#include <bits/extc++.h>
#define x first
#define y second
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
typedef pair<int,int> PAIR;
int n;
PAIR shoes[N];
int vis[N];
int a[N];
int cnt = 0;
int ans = 0;
int q[N];
map <int,list<int> > m;
void merge(int l,int r)
{
    int b[N];
    cnt = 0;
    int mid = (l+r) / 2;
    int p1 = l,p2 = mid+1 ;
    while(p1 <= mid && p2 <= r)
    {
        if(a[p1] <= a[p2])
        {
            b[++cnt] = a[p1];
          //  ans ++;
            p1 ++;
        }
        else 
        {
            b[++cnt] = a[p2];
            p2 ++;
            ans += (mid+1-p1);
        }
    }
    while(p1 <= mid) b[++cnt] = a[p1++];
    while(p2 <= r) b[++cnt] = a[p2++];
    cnt = 0;
    for(int i=l;i<=r;i++) a[i] = b[++cnt]; 
}
void sortt(int l,int r)
{
    if(l < r)
    {
        int mid = (l+r) / 2;
        sortt(l,mid);
        sortt(mid+1,r);
        merge(l,r);
    }
}
bool cmp(PAIR a,PAIR b){return a.x < b.x;}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    n *= 2;
    for(int i=1;i<=n;i++)
    {
        int t;
        cin>>q[i];
        m[q[i]].push_back(i);
      //  if(t > 0) shoes[t].x = i;
      //  else shoes[abs(t)].y = i;
    } 
    //int count = 0;
    for(int i=1,count = 0;i<=n;i++)
    {
      //  cout<<count<<endl;
       // if(count > n*2) break;
        if(vis[i]) continue;
        int j = m[-q[i]].front();
        m[q[i]].pop_front();
        m[q[j]].pop_front();
        vis[i] = vis[j] = 1;
        count += 2;
        if(q[i] < 0) a[i] = count - 1,a[j] = count;
        else a[j] = count - 1,a[i] = count;

    }
   // for(int i=1;i<=n;i++) cout<<a[i]<<" ";
 //  cout<<endl;
    sortt(1,n);
    cout<<ans<<endl;
    return 0;
}