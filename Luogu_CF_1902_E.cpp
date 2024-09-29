#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t long long 
using namespace std;
using namespace __gnu_pbds;
const int N = 1000010;
size_t n,cnt,ans;
string s[N];
int nextt[N][50];
size_t vis[N];
size_t all_len;
size_t getnum(char x) 
{
    if(x>='A'&&x<='Z')
        return x-'A';
    else if(x>='a'&&x<='z')
        return x-'a'+26;
    else
        return x-'0'+52;
} 
void build(string t)
{
    int p = 0;
    for(int i=0;i<t.size();i++)
    {
        int c = getnum(t[i]);
        if(nextt[p][c]) p = nextt[p][c];
        else
        {
            nextt[p][c] = ++cnt;
            p = nextt[p][c];
        }
        vis[p] ++;
    }
}
size_t query(string t)
{
    int p = 0;
    size_t sum = 0;
    for(int i=0;i<t.size();i++)
    {
        int c = getnum(t[i]);
        if(nextt[p][c])
        {
            p = nextt[p][c];
            sum += vis[p];
        }
        else return sum;
    }
    return sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(size_t i=1;i<=n;i++)
    {
        cin>>s[i];
        string t = s[i];
        all_len += t.size();
        reverse(t.begin(),t.end());
        build(t);
    }  
    for(size_t i=1;i<=n;i++)
    {
        string t = s[i];
        ans += (all_len + n*t.size()-2*query(t));
    }
    cout<<ans<<endl;
    return 0;
}