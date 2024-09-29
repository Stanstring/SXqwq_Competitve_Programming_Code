#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int N = 1010;
size_t n;
size_t ans;
size_t a[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(size_t i = 1;i <= n;i ++)
        cin>>a[i];
    for(size_t i = 1;i <= n;i ++) 
        ans += 1/(double)(1*1.0/a[i]*1.0);
    cout<<ans<<endl; 
}