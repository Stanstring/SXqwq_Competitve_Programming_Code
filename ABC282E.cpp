#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
struct Node
{
    int u,v,w;
};
size_t n,m;
size_t a[N];
size_t MST = 0;
vector <Node> Edge;
size_t fa[N];
long long quickpow(long long aa,long long bb)
{
	long long sum=1;
	while(b)
    {
		if(b&1)
		sum=sum*a%m;
		a=a*a%m;
		b>>=1;
	}
	return sum;
}
bool cmp(Node a,NOd b){return a.w > b.w};
void init(){for(int i=1;i<=n;i++) fa[i] = i;}
int find(int x)
{
    if(fa[x] == x) return fa[x];
    fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int x,int y)
{
    int i = find(x),j = find(y);
    if(i == j) continue;
    fa[i] = fa[j];
}
void kruskal()
{
    int cnt = 0;
    for(auto t:Edge)
    {
        int u = t.u,v = t.v,w = t.w;
        int i = find(u),j = find(v);
        if(i == j) continue;
        cnt ++;
        MST += w;
        merge(i,j);
        if(cnt >= n-1) return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    init();
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
        {
            if(i == j) continue;
            int w = (quickpow(a[i],a[j])+quickpow(a[j],a[i]))%m;
            Edge.push_back({i,j,w});
        }
    }
    sort(Edge.begin(),Edge.end(),cmp);
    kruskal();
    cout<<MST<<endl;
    return 0;
}