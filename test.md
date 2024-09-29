## Kruskal 重构树学习笔记

前置知识：Kruskal 最小/最大生成树，倍增。

Kruskal 重构树建立后，可在 $\log$ 的时间复杂度内求出 **两点在最小生成树上的路径最大值**，以及**经过不大于 $w$ 的边能到达的点**。

Kruskal 重构树近几年考察较少，但若遇到类似问题非常适用。

典例：[NOIP2013tg 货车运输](https://www.luogu.com.cn/problem/P1967)，[NOI2018归程](https://www.luogu.com.cn/problem/P4768)。下文会提及。

### Build

不失一般性地，下文 Kruskal 算法均指**最小生成树算法**。

Kruskal 算法执行过程中，我们将边按其权值升序排序，若边两端点互相不可达（即不在一个并查集内），我们加入该边，且合并并查集。

而建立重构树时，我们新建一个虚点 $tot$,点权为加入边的边权。并将合并两个集合的 root 作为该虚点的左右儿子，且将两个集合及虚点合并（以虚点为并查集 root）。

例如，对于下面无向图：
![](https://img2022.cnblogs.com/blog/1858158/202209/1858158-20220905232603319-1940904427.png)

（图片引自 [rui_er 的博客](https://www.cnblogs.com/ruierqwq/p/kruskal-reconstruction-tree.html)，下图同。侵删）

其 Kruskal 重构树如下。

![](https://img2022.cnblogs.com/blog/1858158/202209/1858158-20220905232617980-709999003.png)

（带有 “*” 标记的为虚点。粉色数字为边权。虚点编号都比预期大 $1$。）

代码实现如下。（摘自[归程](https://www.luogu.com.cn/problem/P4768)）

```cpp
    void kruskal()
    {
        dsu.init(); // 初始化并查集
        sort(edge.begin(),edge.end()); // 将边排序
        int noww = n; // 虚点编号
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),a = t.a;
            if(u == v) continue;
            val[++noww] = a; // 存储边权
            dsu.merge(u,noww); // 分别合并虚点和u,v的 root
            dsu.merge(v,noww);
            et[noww].push_back(u); // 连边
            et[noww].push_back(v);
        }
    }
```

### 性质

- 重构树是一棵恰好有 $n$ 个叶子节点的完全二叉树，且叶子节点均为 **原 Kruskal 最小生成树上的点**，非叶子节点均为虚点。

- 重构树的点权符合大跟堆的性质。

- **原图中两点间所有简单路径的最大边权最小值，等于重构树上两点 LCA 的点权。**

- **到点 $u$ 的简单路径上最大边权最小值 $\le k$ 的所有节点 $v$ 均在重构树上的某棵子树内，且恰为该子树内的所有叶子节点。**

后两条性质用的最多。

## 例题

### [NOI2018] 归程

[Source](https://www.luogu.com.cn/problem/P4768)

#### Description

给定一张无向图。每条边有两个参数 $l,a$。$q$ 次询问，每次询问给定两个参数 $v,p$ 表示出发节点及 **不能免费走 $a\le p$** 边。且 **必须连续免费，若走到一条不免费的边，后续边默认不得免费**。对于每次询问，求满足限制前提下，从起点 $v$ 走到 $1$ 节点最小花费 $\sum l$。

$n\le 2\times 10^5,m\le 4\times 10^5$，时限 4s，强制在线。

#### Solution

也算是网红题了。自 NOI2018 后卡 SPFA 成为业界常识了（

显然，这是一个最短路问题。关键在于解决免费走边问题。

我们能免费走一些边，一条边能免费走当且仅当 $a>p$。但我们**必须连续免费走边**，那我们可以从**起点能免费到达的任意节点，开始跑最短路，取最小值即可。**

问题在于如何快速找到一个节点能免费到达的所有节点，即只能走 $a>p$ 的边能到达的节点。这个用 Kruskal 重构树即可。建出 Kruskal 重构树后，我们倍增跳，跳到的虚点下所有儿子均可免费到达。

但这样直接做复杂度还是不对，注意到 **我们是静态查询**，最短路只需做一遍。如果对于每个虚点，我们都知道它下面儿子的距离最小值就好了。

这也很简单，跑完最短路 dfs 扫一下重构树即可。如下。

```cpp
    void dfs(int u,int fat)
    {
        fa[u][0] = fat;
        for(int i=1;i<=19;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        for(auto v:et[u])
        {
            dfs(v,u);
            dis[u] = min(dis[u],dis[v]);
        }
    }
```

需要注意，dfs 从根节点（$2\times n-1$） 开始扫。回溯的时候做一遍递推即可。

如此我们便可做到 $\log n$ 查询。倍增跳到所求虚点后直接输出即可。

<details>
<summary>参考代码</summary>

```cpp
namespace solution
{
    typedef pair<int,int> PAIR;
    struct Node
    {
        int u,v,a;
        bool operator< (const Node& t)const{
            return t.a < a;
        }
    };
    vector <Node> edge;
    vector <PAIR> Edge[N];
    vector <int> et[N];
    int val[N];
    int dis[N],vis[N];
    int fa[N][50];
    int n,m;
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=2*n;i++) fa[i] = i;}
        int find(int x)
        {
            if(x == fa[x]) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        }
        bool merge(int x,int y)
        {
            int i = find(x),j = find(y);
            if(i == j) return 0;
            fa[i] = j;
            return 1;
        }
    }dsu;
    void dfs(int u,int fat)
    {
        fa[u][0] = fat;
        for(int i=1;i<=19;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        for(auto v:et[u])
        {
            dfs(v,u);
            dis[u] = min(dis[u],dis[v]);
        }
    }
    void dijkstra(int s)
    {
        #define x first
        #define y second
        memset(dis,INF,sizeof(dis));
        memset(vis,0,sizeof(vis));
        priority_queue <PAIR> q;
        dis[s] = 0;
        q.push(PAIR(0,s));
        while(!q.empty())
        {
            PAIR p = q.top();
            int u = p.y;
            q.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(auto t:Edge[u])
            {
                int v = t.x,l = t.y;
                if(dis[v] > dis[u] + l)
                {
                    dis[v] = dis[u] + l;
                    q.push(PAIR(-dis[v],v));
                }
            }
        }
    }
    void kruskal()
    {
        dsu.init();
        sort(edge.begin(),edge.end());
        int noww = n;
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),a = t.a;
            if(u == v) continue;
            val[++noww] = a;
            dsu.merge(u,noww);
            dsu.merge(v,noww);
            et[noww].push_back(u);
            et[noww].push_back(v);
        }
    }
    void memset0()
    {
        memset(val,0,sizeof(val));
        memset(fa,0,sizeof(fa));
        for(int i=1;i<=n;i++) Edge[i].clear();
        for(int i=1;i<=2*n;i++) et[i].clear();
        edge.clear();
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++) 
        {
            int u,v,l,a;
            cin>>u>>v>>l>>a;
            edge.push_back({u,v,a});
            Edge[u].push_back(PAIR(v,l));
            Edge[v].push_back(PAIR(u,l));
        }
        dijkstra(1);
        kruskal();
        dfs(2*n-1,0);
        int q,k,s;
        cin>>q>>k>>s;
        int lst = 0;
        while(q--)
        {
            int v,p;
            cin>>v>>p;
            v = (v+k*lst-1)%n+1;
            p = (p+k*lst)%(s+1);
            for(int i = 19;i>=0;i--)
            {
                if(val[fa[v][i]] > p) v = fa[v][i];
            }
            cout<<dis[v]<<endl;
            lst = dis[v];
        }
        memset0();
    }
    void main()
    {
        int T;
        cin>>T;
        while(T--) solve();
    }
}
```
</details>

### P9638 「yyOI R1」youyou 的军训

[Source](https://www.luogu.com.cn/problem/P9638)

#### Description

共有 $q$ 次操作。

- `1 x` 断开边权 $< x$ 的边，并恢复先前操作断开的边。

- `2 x` 询问点 $x$ 所位于连通块大小。即点 $x$ 能到达多少个点（包括本身。）

- `3 x y` 将编号为 $x$ 的边权值修改为 $y$，保证修改后边权相对大小不变。

$n,q\le 4\times 10^5$。
#### Solution


注意到操作 $1$ 之间互不影响，故查询时，**一条边能走当且仅当边权 $\ge limit$**。（$limit$ 在操作 $1$ 时更新。）

我们将边按照权值从大到小排序，建立 Kruskal 重构树。找到点 $x$ 向上跳到最小的满足边权 $\ge x$ 的边，以其为父节点，下面叶子节点数量即为答案。（在 Kruskal 重构树中，叶子节点即为实点。）

因此，建出 Kruskal 重构树后，我们预处理出**每个虚点下面叶子节点的数量，记为 $size$**。这很简单，dfs 扫一遍即可。

对于操作 $1$，更新当前限制 $limit$。（$limit$ 表示点 $x$ 仅允许走边权 $\ge limit$ 的边。）

对于操作 $3$，题目保证**修改后边权的相对大小不变**。即 Kruskal 重构树形态不变。在读入边时，我们记录每条边的编号，在 Kruskal 重构树上单点修改即可。

对于操作 $2$，我们倍增查询。这就用到了先前处理的 $size$ 数组。向上跳到最小的符合条件的边，输出其 $size$ 值即可。

<details>

<summary>参考代码</summary>

```cpp
namespace solution
{
    constexpr int N = 1000010;
    typedef pair<int,int> PAIR;
    int n,m,q,limi;
    int tot;
    struct Node
    {
        int u,v,w,id;
        bool operator <(const Node& a)const{
            return a.w < w;
        }
    };
    vector <Node> edge;
    vector <PAIR> Edge[N];
    int edge_num[N],fa[N][50],siz[N];
    int val[N];
    struct DSU
    {
        int fa[N];
        void init(){for(int i=1;i<=n*2+1;i++) fa[i] = i;}
        int find(int x)
        {
            if(x == fa[x]) return x;
            fa[x] = find(fa[x]);
            return fa[x];
        } 
        void merge(int x,int y)
        {
            int i = find(x),j = find(y);
            if(i == j) return;
            fa[i] = j;
        }
    }dsu;
    void kruskal()
    {
        sort(edge.begin(),edge.end());
        tot = n; 
        dsu.init();
        for(auto t:edge)
        {
            int u = dsu.find(t.u),v = dsu.find(t.v),w = t.w;
            if(u == v) continue;
            tot ++;
            dsu.merge(u,tot),dsu.merge(v,tot);
            Edge[tot].push_back(PAIR(u,w)),Edge[tot].push_back(PAIR(v,w));
            edge_num[t.id] = tot;
            val[tot] = w;
        }
    }
    void dfs(int u,int fat)
    {
        #define x first
        #define y second
        for(int i=1;i<=30;i++) fa[u][i] = fa[fa[u][i-1]][i-1];
        if(u <= n) 
        {
            siz[u] = 1;
            return;
        }
        for(auto t:Edge[u])
        {
            int v = t.x;
            if(siz[t.x] || t.x == fat) continue;
            fa[t.x][0] = u;
            dfs(t.x,u);
            siz[u] += siz[v];
        }
    }
    int find_max(int u)
    {
        for(int i=30;i>=0;i--)
            if(fa[u][i] && val[fa[u][i]] >= limi) u = fa[u][i];
        return u;
    }
    void solve()
    {
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            edge.push_back({u,v,w,i});
        }
        kruskal();
        cerr<<tot<<endl;
        for(int i=tot;i;i--) if(!siz[i]) dfs(i,0);
        while(q--)
        {
            int op;
            cin>>op;
            if(op == 1) 
                cin>>limi;
            else if(op == 2)
            {
                int x;
                cin>>x;
                cout<<siz[find_max(x)]<<endl;
            }
            else if(op == 3)
            {
                int x,y;
                cin>>x>>y;
                val[edge_num[x]] = y;
            }
        }
        return;
    }
}
```
</details>