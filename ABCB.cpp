#include <bits/stdc++.h>
using namespace std;
namespace solution
{
    void solve()
    {
        int sum = 0;
        string s;
        cin>>s;
        int res = 0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i] == 'A') {res = i;break;}
        }
        for(int i=1;i<=25;i++)
        {
            char c = char('A'+i);
          //  cerr<<c<<endl;
            int add = 0;
            for(int j=0;j<s.size();j++)
            {
                if(s[j] == c)
                {
                    add = j;
                    break;
                }
             //   cerr<<add<<" "<<res<<endl;
   
        }
                     sum += abs(add-res);
                res = add;
        }
        cout<<sum<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}