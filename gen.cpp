#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
signed main()
{
    freopen("input.in","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout<<"100000 100000"<<endl;
    for(int i=1;i<=100000;i++)
    {
        cout<<i<<" ";
    } 
    cout<<endl;
    for(int i=1;i<=100000;i++)
    {
        cout<<i+100000<<" "<<i+200000<<endl;
    }
    return 0;
}