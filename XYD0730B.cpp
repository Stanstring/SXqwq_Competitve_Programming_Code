#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
int n,m;
int a[N];
__int128_t qwq = 0;
bool cmp(int a,int b){return a>b;}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,cmp);
    int p,q;
    while(m--)
    {
        cin>>p>>q;
        qwq = 0;
        bool get_ans = 0;
        for(int i=1;i<=n;i++) 
        {
            qwq += p*a[i];
            p--;
            if(qwq >= q) 
            {
                cout<<i<<endl;
                get_ans = 1;
                break;
            }
        }
        if(!get_ans) cout<<"-1"<<endl;
    }
}