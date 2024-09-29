#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define y1 yy
using namespace std;
int n,m,x,y,l;
int ans,x1,y1;
int exgcd(int a,int b,int &x1,int &y1)
{
    if(!b) 
    {
        x1 = 1;
        y1 = 0;
        return a;
    }
    ans = exgcd(b,a%b,x1,y1);
    int t = x1;
    x1 = y1;
    y1 = t-a/b*y1;
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>x>>y>>m>>n>>l;
    int b = n-m,a = x-y;
    if(b < 0)
    {
        b = -b;
        a = -a;
    }
    exgcd(b,l,x1,y1);
    if(a%ans != 0) cout<<"Impossible"<<endl;
    else cout<<((x1*(a/ans))%(l/ans)+(l/ans))%(l/ans)<<endl;
    return 0;
}