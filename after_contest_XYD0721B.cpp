#include <bits/stdc++.h>
#include <bits/extc++.h>
#define x first 
#define y second
using namespace std;
using namespace __gnu_pbds;
typedef pair<size_t,size_t> PAIR;
constexpr int N = 8010;
size_t n,m,c;
vector <PAIR> qwq[N];
size_t limi[N];
size_t f[N][N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>c;
    for(size_t i=1;i<=n;i++)
    {
        size_t v,w,c;
        cin>>v>>w>>c;
        qwq[c].push_back(PAIR(v,w));
    }
    for(size_t i = 1;i <= c;i++)
    {
        cin>>limi[i];
        for(auto t:qwq[i])
        {
            size_t v = t.x,w = t.y;
            for(int j = min(m,limi[i]);j >= w;j --)
                f[i][j] = max(f[i][j],f[i][j-w]+v);
        }
    }
    size_t f1[N];
    fill(f1+1,f1+n+1,0);
    for(size_t i = 1;i <= c;i++)
    {
        for(size_t j = m;j >= 1;j--)
        {
            for(size_t k = 1;k <= min(j,limi[i]);k ++) 
                f1[j] = max(f1[j],f1[j-k]+f[i][k]);
        }
    }
    cout<<f1[m]<<endl;
    return 0;
}