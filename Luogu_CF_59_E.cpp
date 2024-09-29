#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 801000;
constexpr int INF = 0x3f3f3f3f;
map <tuple<int,int,int>,bool> mapp;
typedef tuple<int,int,int> Tuple;
int n,m,k;
int vis[N];
bool u[N];
vector <int> Edge[N];
int ecnt;
int fst[N];
struct QWQ
{
    int to,nxt;
}e[N];
struct Node
{
    int u,last,dist,from;
}q[N];
void print(int x)
{
    if(q[x].from) print(q[x].from);
    cout<<q[x].u<<" ";
}
void edge(int sta,int edn){
	ecnt++;
	e[ecnt]={edn,fst[sta]};
	fst[sta]=ecnt;
}
void bfs()
{
    q[1].u = 1;
    int head,tail;
    head = tail = 1;
    while(head <= tail)
    {
        Node p = q[head];
        for(int E=fst[p.u];E;E = e[E].nxt)        
        {
            if(u[E] || mapp[Tuple(p.last,p.u,e[E].to)]) continue;
            if(e[E].to == n)
            {
              //  cout<<mapp[Tuple(p.last,p.u,e[E].to)]<<endl;
             //   cout<<p.last<<" "<<p.u<<" "<<e[E].to<<"is ok"<<endl;
                cout<<p.dist + 1<<endl;
                print(head);
                cout<<n<<endl;
                exit(0);
            }
            u[E] = 1;
            tail ++;
            q[tail]={e[E].to,p.u,p.dist+1,head};
        }
        head ++;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        edge(u,v);
        edge(v,u);
    }
    for(int i=1;i<=k;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        mapp[Tuple(a,b,c)] = 1;
      //  cout<<a<<" "<<b<<" "<<c<<"qwq"<<endl;
       // cout<<mapp[make_tuple(a,b,c)]<<endl;
    }
    bfs();
    cout<<"-1"<<endl;
}