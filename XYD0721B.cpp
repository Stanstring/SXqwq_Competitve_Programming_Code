#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int N = 1010;
size_t T,n;
string s,t;
size_t f[N][N];
bool check()
{
    for(size_t i = 0;i<s.size()-1;i++)
        if(s[i] == s[i+1]) return 0;
    for(size_t i = 0;i<t.size()-1;i++) 
        if(t[i] == t[i+1]) return 0;
    for(size_t i = 1 ;i<=s.size();i++)
    {
        for(size_t j = 1;j<=t.size();j++) 
        {
            if(s[i-1] == t[j-1]) f[i][j] = f[i-1][j-1] + 1;
            else if(f[i-1][j] >= f[i][j-1]) f[i][j] = f[i-1][j];
            else f[i][j] = f[i][j-1];
        }
    }    
    cout<<f[s.size()][t.size()]<<endl;
    return f[s.size()][t.size()] == n;
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
        cin>>s>>t;
        if(check()) cout<<"1"<<endl;
        else cout<<"0"<<endl;
    }
}