#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
size_t n,m,x;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    if(n > m) swap(n,m);
    if(n == 1) x = m/3+(m%3!=0);
    if(n == 2) x = m/2+1;
    if(n == 3) x = m-(m-1)/4;
    if(n == 4) x = (m+1)-(m == 4 || m == 7 || m == 8 || m == 10);
    if(n == 5) x = 7*(m == 5)+8*(m == 6)+9*(m == 7) + 11 * (m == 8);
    if(n == 6) x = 10;
    cout<<n*m-x<<endl;
    return 0;
}