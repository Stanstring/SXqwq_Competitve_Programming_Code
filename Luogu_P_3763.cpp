#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
constexpr int p = 113;
int T;
string s0,s;
size_t pp[N],f[N],g[N];
size_t gethash(size_t t[],int le,int re)
{
    return t[re]-t[le-1]*pp[re-le+1];
}
bool check(int l,int ed)
{
    int st = 1,rt = l+ed-1;
    for(int i=1;i<=3;i++)
    {
        int le = -1,re = ed-st+2;
        while(le < re-1)
        {
            int mid = (le+re) >> 1;
            size_t hash1 = gethash(f,l,l+mid-1),hash2 = gethash(g,st,st+mid-1);
            if(hash1 == hash2) le = mid;
            else re = mid;
        }
        l += le + 1;
        st += le + 1;
        if(st > ed) return 1;
    }
    return gethash(f,l,rt) == gethash(g,st,ed);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    pp[0] = 1;
    for(int i=1;i<=N;i++) pp[i] = pp[i-1]*p;
    while(T--)
    {
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        cin>>s>>s0;
        if(s0.size() > s.size()) {cout<<"0"<<endl;continue;}
        int len1 = s.size(),len2 = s0.size();
        s0 = "0"+s0;
        s = "0"+s;
        for(int i=1;i<=len1;i++) f[i] = f[i-1]*p+s[i];
        for(int i=1;i<=len2;i++) g[i] = g[i-1]*p+s0[i];
        int ans = 0;
        for(int i=1;i+len2-1 <= len1;i++)
        {
            if(check(i,len2)) ans ++;
        }
        cout<<ans<<endl;
    }
}