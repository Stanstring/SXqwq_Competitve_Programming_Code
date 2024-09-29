#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
const int N = 1000010;
size_t P[100]= {2,3,5,7,11,13,17,19,23,29,31};
int n,a[N],p[N],q[N];
int f[1<<12],d[1<<12];
int T;
vector <int> Edge[N];
void init()
{
    for(int i=1;i<=1000;i++) Edge[i].clear();
    cin>>n;
}
void solve()
{
    init();
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        q[i] = a[i];
        p[i] = 0;
        for(int k=0;k<11;k++) 
        {
            if(q[i] % P[k] == 0) 
            {
                p[i] |= (1<<k);
                while(q[i] % P[k] == 0) q[i] /= P[k];
            }
        }    
        Edge[q[i]].push_back(i);
    }
    fill(f+1,f+(1<<11),-1);
    f[0] = 0;
    for(auto i:Edge[1])
    {
        copy(f,f+(1<<11),d);
        for(int j=0;j<(1<<11);j++) 
        {
            if(f[j] != -1 && (j&p[i]) == 0) 
            {
                auto &v = d[j|p[i]];
                v = max(v,f[j] + 1);
            }
        }
        copy(d,d+(1<<11),f);
    }
    for(int k=2;k<=1000;k++)
    {
        if(Edge[k].size())
        {
            copy(f,f+(1<<11),d);
            for(auto i:Edge[k])
            {
                for(int j=0;j<(1<<11);j++)
                {
                    if(f[j] != -1 && (j&p[i]) == 0)
                    {
                        auto &v = d[j|p[i]];
                        v = max(v,f[j] + 1);
                    }
                }
            }
            copy(d,d+(1<<11),f);
        }
    }
    int maxn = 1;
    for(int i=0;i<(1<<11);i++) maxn = max(maxn,f[i]);
    cout<<maxn<<endl;
    return;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--) solve();
}