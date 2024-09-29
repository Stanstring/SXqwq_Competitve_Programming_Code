#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 0x3f;
typedef pair<int,int> PAIR;
int h,dis[N];
int ans = 0;
int x,y,z;
vector <PAIR> Edge[N];
int vis[N];
void bfs()
{
    memset(dis,-1,sizeof(dis));
    queue <PAIR> q;
    q.push(PAIR(0,0));
    dis[0] = 1;
    while(!q.empty())
    {
        PAIR p = q.front();
        q.pop();
        int x = p.second;
        if(vis[x]) continue;
        vis[x] = 1 ;
        for(auto t:Edge[x])
        {
            int yy = t.first,zz = t.second;
            if(dis[yy] > dis[x] + zz || dis[yy] == -1)
            {
                dis[yy] = dis[x] + zz;
                q.push(PAIR(-dis[yy],yy));
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>h;
    h --;
    cin>>x>>y>>z;
    if(x<y) swap(x,y);
	if(x<z) swap(x,z);
    for(int i = 0 ;i < x;i++)
    {
        Edge[i].push_back(PAIR((i+y)%x,y));
        Edge[i].push_back(PAIR((i+z)%x,z));
    }
    bfs();
    for(int i=0;i<x;i++)
    {
        if(h >= dis[i] && dis[i] != -1) 
            ans += (h-dis[i])/x+1;
    }
    cout<<ans+1<<endl;
    return 0;
}