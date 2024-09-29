#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 100010;
int sum = 0;
int n,l;
int cnt =0;
char bca[N];
signed main()
{
   // freopen("ex_bracket4.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>l;
    int left = 0;
    int count = 0;
    for(int i=1;i<=n;i++)
    {
        char ch;
        cin>>ch;
        if(ch == ')')
        {
            if(!left)
            {
                left ++;
                count ++;
            }
            else
            {
                left --;
            }
        }
        else
        {
            left ++;
            if(left > l)
            {
                count ++;
                left -=2;
            }
        }
    }
    if(left > l)
    {
        int p = left-l;
        left -= (p);
        count +=(p);
    }
    cout<<count + left<<endl;
}