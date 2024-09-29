#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
const int N = 10010;
using namespace __gnu_pbds;
vector <int> Edge[N];
int n,root;
int f[N][5];
int in[N];
void dfs(int u,int fat)
{
    f[u][0] = 0;
    f[u][1] = 1;
    for(auto v:Edge[u])
    {
        if(v == fat) continue;
        dfs(v,u);
        f[u][0] += f[v][1];
        f[u][1] += min(f[v][0],f[v][1]);
    }
}
int main()
{
    while(cin>>n)
    {
        for(int i=0;i<n;i++) Edge[i].clear();
        memset(f,0,sizeof(f));
        memset(in,0,sizeof(in));
        for(int i=0;i<n;i++)
        {
                    int u,k,v;
        scanf("%d:(%d)",&u,&k);
        for(int i=1;i<=k;i++)
        {
            cin>>v;
            Edge[u].push_back(v);
            Edge[v].push_back(u);
            in[v] ++;
        }
        }

        for(int i=0;i<n;i++) 
        {
            if(!in[i]) 
            {
                root = i;
                break;
            }
        } 
        dfs(root,-1);
        cout<<min(f[root][0],f[root][1])<<endl;
    }
}