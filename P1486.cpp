#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
struct Node
{
    int v,id;
    Node(int a,int b) 
    {
        v = a;
        id = b;
    }
    bool operator >(Node b) const
    {
        return v == b.v?id > b.id:v>b.v;
    }
};
tree <Node,null_type,greater<Node>,rb_tree_tag,tree_order_statistics_node_update> TREE,Tree;
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int n,m,k,s = 0,ans = 0;
    cin>>n>>m;char op;
    while(n--)
    {
        
        cin>>op;
        cin>>k;
        if(op == 'I') 
        {
            k += s;
            if(k >= m) 
            {
                TREE.insert({k,n});
            }
        }
        else if(op == 'A') 
        {
            m -= k;
            s -= k;
        }
        else if(op == 'S')
        {
            m += k;
            s += k;
            TREE.split({m,-1},Tree);
            ans += Tree.size();
        }
        else 
        {
            printf(k>TREE.size()?"-1\n":"%d\n",TREE.find_by_order(k-1)->v-s);  
        }
    }
    cout<<ans<<endl;
    return 0;
}