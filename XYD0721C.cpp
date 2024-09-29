#include <bits/stdc++.h>
#include <bits/extc++.h>
#define size_t long long
#define x first 
#define y second
using namespace std;
using namespace __gnu_pbds;
typedef pair<size_t,size_t> PAIR;
const int N = 1000100;
int n,m,c;
int maxn_sub1 = 0;
int limi[N];
struct Node
{
    int v,w,c;
}qwq[N];
bool cmp_sub1(Node a,Node b){return a.c < b.c;}
void dfs_sub1(int pos,int allheight,int val,int chight,int last_pos) //force
{
    if(pos > n) 
    {
        if(allheight > m) return;
        maxn_sub1 = max(maxn_sub1,val);
        return;
    }
    int cchight = chight,allhightt = allheight;
    if(qwq[pos].c != qwq[last_pos].c) 
    {
        if(qwq[pos].w > limi[qwq[pos].c]) 
        {
            dfs_sub1(pos+1,allheight,val,chight,pos-1);
            return;
        }
        else cchight = qwq[pos].w;
    }
    else 
    {
        if(cchight + qwq[pos].w <= limi[qwq[pos].c]) 
            cchight += qwq[pos].w;
        else 
        {
            dfs_sub1(pos+1,allheight,val,chight,pos-1);
            return;
        }
    }
    if(allhightt + qwq[pos].w <= m) allhightt += qwq[pos].w;
    else goto nxt;
    dfs_sub1(pos+1,allhightt,val+qwq[pos].v,cchight,pos);
    nxt:
    dfs_sub1(pos+1,allheight,val,chight,pos);
}
void subtask1() 
{
  //  cout<<"sub1"<<endl;
    sort(qwq+1,qwq+n+1,cmp_sub1);
    maxn_sub1 = 0;
    dfs_sub1(1,0,0,0,0);
    cout<<maxn_sub1<<endl;
    return;
}
void subtask2() //01 bag
{
    int f[N];
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=qwq[i].w;j--)
        {
            f[j] = max(f[j],f[j-qwq[i].w]+qwq[i].v);
        } 
    }
    cout<<f[m]<<endl;
    return;
}
bool cmp_sub3(PAIR a,PAIR b) {return a.y > b.y;}
vector <PAIR> QWQ[N];
void subtask3()
{
    size_t answer = 0,noww;
    for(int i=1;i<=n;i++) QWQ[qwq[i].c].push_back(PAIR(qwq[i].w,qwq[i].v));
    for(int i=1;i<=c;i++) sort(QWQ[i].begin(),QWQ[i].end(),cmp_sub3); 
    for(int i=1;i<=c;i++)
    {
        noww = 0;
        for(auto t:QWQ[i])
        {
            int w = t.x,v =t.y;
            if(noww + 1 > limi[i]) break;
            noww ++;
            answer += v;
        }
    }
    cout<<answer<<endl;
    return;
}
void Check_Subtask_solve()
{
    if(n <= 15) 
    {
        subtask1();
        return;
    }
    bool is_sub2 = 1;
    for(size_t i=1;i<=c;i++)
    {
        if(limi[i] > m) {is_sub2 = 0;break;}
    }
    if(is_sub2) {subtask2();return;}
    bool is_sub3 = 1;
    for(size_t i = 1;i<=n;i++) 
    {
        if(qwq[i].w != 1) {is_sub3 = 0;break;}
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>c;
    for(size_t i=1;i<=n;i++)
        cin>>qwq[i].v>>qwq[i].w>>qwq[i].c;
    for(size_t i = 1;i <= c;i++) cin>>limi[i];
    Check_Subtask_solve();
}