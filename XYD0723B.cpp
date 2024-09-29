#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t int
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 5050;
size_t T;
size_t n;
size_t a[N];
vector <int> qwq[N];
int vis[N]; // 每个因数是否可访问
int influence[N];
void get_num(size_t x)
{
    for(int i=x-1;i>1;i--)
    {
        if(!(x%i)) qwq[i].push_back(x);
    }
    qwq[x].push_back(x);
}
int radd()
{
	int i, m, n;
	m = 0;
	n = 1;
	srand((unsigned)time(NULL));
	//for (i = 0; i < 10; i++) {
		int num = rand() % (n-m+1) + m;
        return num;
    //}
}
bool cmp(size_t a,size_t b)
{
    if(influence[a] == influence[b]) return radd();
    return (influence[a] < influence[b]);
}
bool check(int x) 
{
    for(int i=x-1;i>1;i--) 
        if(!(x%i) && vis[i]) return 0;
    return 1;
}
void solve()
{
    for(int i=1;i<=1010;i++) qwq[i].clear();
   memset(vis,0,sizeof(vis));
   memset(influence,0,sizeof(influence));
    for(int i=1;i<=n;i++) //init
        get_num(a[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=a[i]-1;j>1;j--) 
        {
            if(!(a[i]%j)) influence[a[i]] += qwq[j].size()-1;
        }
    }
    int maxn = 0;
    for(int i=1;i<=10;i++)
    {
      //  random_shuffle(a+1,a+n+1);
        sort(a+1,a+n+1,cmp);
     //   for(int i=1;i<=n;i++) cout<<a[i]<<" ";
     //   cout<<endl;
        memset(vis,0,sizeof(vis));
        int ans = 0;
        for(int i=1;i<=n;i++) 
        {
            if(!check(a[i]) || vis[a[i]]) continue;
            ans ++;
            for(int j=a[i]-1;j>1;j--) 
            {
                if(!(a[i]%j)) vis[j] = 1;
            }
        vis[a[i]] = 1;
        }
        maxn = max(maxn,ans);
    }
   // sort(a+1,a+n+1,cmp);
  
    cout<<maxn<<endl;
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        solve();
    }
}