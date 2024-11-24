#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<ll> c(n+1);
    for(int i=1; i<=n; i++) cin >> c[i];
    
    // 构建树的邻接表
    vector<vector<pair<int, ll>>> tree(n+1);
    for(int i=1; i<n; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }
    
    // f1[u]: 子树内的最大值
    vector<ll> f1(n+1, LLONG_MIN);
    // top1[u], top2[u]: 子节点中前两大的 f1[v] - 2*w(u,v)
    vector<ll> top1(n+1, LLONG_MIN);
    vector<ll> top2(n+1, LLONG_MIN);
    
    // 第一次DFS，计算f1和top1、top2
    function<void(int, int)> dfs1 = [&](int u, int parent) {
        f1[u] = c[u]; // 初始化为自身
        for(auto &[v, w]: tree[u]){
            if(v == parent) continue;
            dfs1(v, u);
            ll temp = f1[v] - 2 * w;
            // 更新top1和top2
            if(temp > top1[u]){
                top2[u] = top1[u];
                top1[u] = temp;
            }
            else if(temp > top2[u]){
                top2[u] = temp;
            }
            // 更新f1[u]
            f1[u] = max(f1[u], temp);
        }
    };
    
    // 假设1为根节点
    dfs1(1, -1);
    
    // f2[u]: 非子树部分的最大值
    vector<ll> f2(n+1, LLONG_MIN);
    
    // 第二次DFS，计算f2
    function<void(int, int)> dfs2 = [&](int u, int parent) {
        for(auto &[v, w]: tree[u]){
            if(v == parent) continue;
            // 计算f2[v]
            // option1: 来自父节点的f2[u]减去边权
            ll option1 = f2[u] - 2 * w;
            // option2: 来自兄弟的top1或top2
            ll temp = f1[v] - 2 * w;
            ll option2;
            if(top1[u] == temp){
                option2 = top2[u] - 2 * w;
            }
            else{
                option2 = top1[u] - 2 * w;
            }
            // 选择更大的值
            ll candidate = max(option1, option2);
            // 也考虑来自父节点的直接贡献
            candidate = max(candidate, c[u] - 2 * w);
            // 更新f2[v]
            f2[v] = max(f2[v], candidate);
            // 递归处理子节点
            dfs2(v, u);
        }
    };
    
    // 从根节点开始，f2[root]保持LLONG_MIN
    dfs2(1, -1);
    
    // 计算最终的f[u] = max(f1[u], f2[u])
    vector<ll> f(n+1, LLONG_MIN);
    for(int u=1; u<=n; u++) f[u] = max(f1[u], f2[u]);
    
    // 输出结果
    for(int u=1; u<=n; u++) cout << f[u] << ' ';
    cout << '\n';
    
    return 0;
}