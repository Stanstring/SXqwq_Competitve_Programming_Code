#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1000010;
constexpr int INF = 100010;
namespace solution
{
    #define ls p<<1
    #define rs p<<1|1
    int n,m;
    int mi;
    struct segtree
    {
        int tree[N*8];
        
        void pushup(int p){tree[p] = tree[ls] + tree[rs];}
        void newedge(int l,int r,int p,int pos,int d)
        {   
            if(l == r) 
            {
                tree[p] += d;
                return;
            }
            int mid = (l+r) >> 1;
            if(pos <= mid) newedge(l,mid,ls,pos,d);
            else newedge(mid+1,r,rs,pos,d);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return 0;
            if(l >= pl && r <= pr) return tree[p];
            int mid = (l+r) >>1;
            return query(l,mid,pl,pr,ls) + query(mid+1,r,pl,pr,rs);
        }
        int query_k(int l,int r,int p,int k)
        {
            //  cerr<<mi<<"qwq"<<endl;
            if(l == r) return l;
            int mid = (l + r) >> 1, l1 = -1, r1 = -1;
            if(k <= tree[rs]) return query_k(mid+1,r,rs,k);
            else return query_k(l,mid,ls,k-tree[rs]);
        }
        void cleant(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return;
            if(l == r) {tree[p] = 0;return;}
            int mid = (l+r) >> 1;
            if(pl <= mid && tree[ls]) 
                cleant(l,mid,pl,pr,ls);
            if(pr >= mid && tree[rs])
                cleant(mid+1,r,pl,pr,rs);
            pushup(p);
        }
    }seg;
    void solve()
    {
        cin>>n>>m;
        int limi = m;
        
        int ans = 0;
        int b = 0;
        m += INF;
        while(n--)
        {
            int k;
            char op;
            cin>>op>>k;
            if(op == 'I')
            {
                if(k < limi) continue;
                seg.newedge(0,N-1,1,k-b+INF,1);        
            }
            else if(op == 'A')
            {
                m -= k;
                b += k;
            }
            else if(op == 'S')
            {
                m += k;
                b -= k;
                int t = seg.query(0,N-1,0,m-1,1);
                if(m >= 1 && t > 0)
                {
                    ans += t;
                    seg.cleant(0,N-1,0,m-1,1);
                }
            }
            else 
            {
           //     cout<<seg.query(1,N-1,m,N-1,1)<<"qaq"<<endl;
                if(seg.query_k(0,N-1,1,k)+b-INF < 0) cout<<"-1"<<endl;
                
                else cout<<seg.query_k(0,N-1,1,k)+b-INF<<endl;
            }
        }
        cout<<ans<<endl;
        return;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}