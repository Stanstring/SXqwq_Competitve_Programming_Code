#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
const int N = 305;
int f[N][N];
int n;

int solve(int l,int r)
{
  //  cout<<l<<" "<<r<<endl;
    int ans = 0;
    if(l == r)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) 
            {
               // if(!(~dis[i][k] && ~dis[k][j])) continue;
                if(i == l || j == l) continue;
                ans += f[i][j];
            }
        }
        return ans;
    }
    int cpy[N][N];
    int mid = l + (r-l>>1);
    memcpy(cpy,f,sizeof(f));
    for(int k=mid+1;k<=r;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(k == i) continue;
            for(int j=1;j<=n;j++) 
            {
                if(j == k || j == i) continue;
                if(~f[i][k] && ~f[k][j])
                {
                    if((~f[i][j])) f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
                    else f[i][j] = f[i][k] + f[k][j];
                }
            }
        }
    }
    ans += solve(l,mid);
    memcpy(f,cpy,sizeof(cpy));
    for(int k=l;k<=mid;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(k == i) continue;                         
            for(int j=1;j<=n;j++)
            {
                if(j == k || j == i) continue;
                if(~f[i][k] && ~f[k][j])
                {
                    if(~f[i][j]) f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
                    else f[i][j] = f[i][k] + f[k][j];
                }
            }
        }
    }
    ans += solve(mid+1,r);
   // cout<<ans<<endl;
    memcpy(f,cpy,sizeof(cpy));
    return ans;
}
signed main()
{
    freopen("1.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) cin>>f[i][j];
    }
    cout<<solve(1,n)<<endl;
    return 0;
}