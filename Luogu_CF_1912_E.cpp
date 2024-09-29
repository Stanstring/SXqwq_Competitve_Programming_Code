#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t long long
#define int long long
using namespace std;
using namespace __gnu_pbds;
size_t a,b;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>a>>b;
    if((a&1) && (b&1)) cout<<"1+",a--,b--;
    if((a&1) && !(b&1)) cout<<"21+",a-=21,b-=12;
    if(!(a&1) && (b&1)) cout<<"12+",a-=12,b-=21;
    int aa = a,bb = b;
    int flg =0;
    if(bb < 0) 
        bb = -bb,flg = 1,cout<<"0-";
    for(int ct = 0;bb;bb/=9,ct++) 
    {
        if(bb % 9)
        {
            cout<<bb % 9;
            for(int i=1;i<=ct;i++) cout<<"*9";
            if(flg) cout<<"-";
            else cout<<"+";
        }
    }
        cout<<"0";
        int x = a-b>>1;
        if(!(x%10))
        {
            if(x > 0) cout<<"+"<<x-1<<"+"<<x-1<<"-0+1+1-0";
            else if(x < 0) cout<<x+1<<x+1<<"+0-1-1";
        }
        else
        {
            if(x > 0) cout<<"+"<<x<<"+"<<x<<"-0";
            else if(x < 0) cout<<x<<x;
        }
       return 0;
}
