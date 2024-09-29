## P1570 KC 喝咖啡

[Source](https://www.luogu.com.cn/problem/P1570)

### Description

给定 $n$ 个元素，每个元素都有 $v_i,c_i$ 两个值。选 $m$ 个元素，使得 $\dfrac{\sum v_i}{\sum c_i}$ 最大。

$n\le 200$。

### Solution 

01 分数规划板子。

令 $\dfrac{\sum v_iw_i}{\sum c_iw_i}\ge mid(w_i\in\{0,1\})$ 然后移项。

$$\sum v_iw_i\ge mid\sum c_iw_i$$

$$\sum v_iw_i\ge \sum c_iw_i mid$$

$$\sum v_iw_i-\sum c_iw_imid\ge 0$$

$$w_i\sum v_i-c_imid\ge 0$$

对于 $\forall mid$，计算 $\forall (v_i-c_imid)$，取前 $k$ 大判断是否大于等于 $0$ 即可。

板子题。

<details>
<summary>Code</summary>

```cpp
namespace solution
{
    constexpr int MAXN = 10000;
    constexpr int INF = 0x3f3f3f3f;
    int n,m;
    int v[N],c[N];
    bool cmp(int a,int b){return a>b;}
    bool check(int x)
    {
        int t[N];
        for(int i=1;i<=n;i++) t[i] = v[i]-c[i]*x;
        sort(t+1,t+n+1,cmp);
        int sum = 0; 
        for(int i=1;i<=m;i++) sum += t[i];
        return sum >= 0;
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++) {cin>>v[i];v[i]*=MAXN;}
        for(int i=1;i<=n;i++) {cin>>c[i];}
        int l = 1,r = 1e6;
        while(l <= r)
        {
            int mid = (l+r) >>1;
            if(check(mid)) l = mid + 1;
            else r = mid - 1;
        }
        printf("%.3lf\n",(double)(l*1.0/MAXN));
        return;
    }
}
```
</details>

## P4281 [AHOI2008] 紧急集合 / 聚会

[Source](https://www.luogu.com.cn/problem/P4281)

### Description

给定一棵有根树，$q$ 次询问，每次询问给定树上三个点 $x,y,z$，求一个点 $t$，使得 $\text{dis}(x,t)+\text{dis}(y,t)+\text{dis}(z,t)$ 最小。$\text{dis}(x,y)$ 表示树上点 $x,y$ 的距离。

$n\le 5\times 10^5$。

### Solution

大胆猜结论题。

首先考虑最简单的情况，若只有两个点，则  $t$ 可在两点路径上的任意位置。

我们让 $\text{dis}(x,t)+\text{dis}(y,t)+\text{dis}(z,t)$ 最小，就是让边尽可能不被重复走，每条边最多只能造成一次贡献。

到这里就可以画图找规律了。通过画图可看出，**若将三点两两求 LCA，一定存在两对点的 LCA 相同**。这个结论是对的。

我们最优点一定选在 LCA 上，若不选 LCA，会出现重复走的情况。

选哪个 LCA 呢？

我们要选 **和另外两对点对不相同的 LCA**。两队点对的 LCA 相同了，选那个相同的 LCA 势必会出现重复走的情况。然后计算答案即可。求 LCA 可以倍增，可以树剖，也可以各种奇怪做法。

<details>
<summary>Code</summary>

```cpp
namespace solution
{
    int n,m;
    vector <int> Edge[N];
    struct TCS
    {
        int dfn[N],siz[N],son[N],fa[N],tp[N],depth[N];
        int cnt = 0;
        void dfs1(int u,int fat)
        {
            fa[u] = fat;
            depth[u] = depth[fat] + 1;
            int maxn = 0,maxx = 0;
            siz[u] = 1;
            for(auto v:Edge[u])
            {
                if(v == fat) continue;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn)
                {
                    maxn = siz[v];
                    maxx = v;
                }
            }
            son[u] = maxx;
        }
        void dfs2(int u,int topp)
        {
            tp[u] = topp;
            dfn[u] = ++cnt;
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto v:Edge[u])
            {
                if(v == son[u] || v == fa[u]) continue;
                dfs2(v,v);
            }
        }
        int get_lca(int u,int v)
        {
            while(tp[u] != tp[v])
            {
                if(depth[tp[u]] > depth[tp[v]]) swap(u,v);
                v = fa[tp[v]];
            }
            if(depth[u] > depth[v]) swap(u,v);
            return u;
        }
    }tcs;
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin>>u>>v;
            Edge[u].push_back(v),Edge[v].push_back(u);
        }
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        while(m--)
        {
            int x,y,z;
            cin>>x>>y>>z;
            int lca1 = tcs.get_lca(x,y),lca2 = tcs.get_lca(x,z),lca3 = tcs.get_lca(y,z);
            int min_lca = min({tcs.depth[lca1],tcs.depth[lca2],tcs.depth[lca3]});
            int max_lca = max({tcs.depth[lca1],tcs.depth[lca2],tcs.depth[lca3]});
            int ans = tcs.depth[x]+tcs.depth[y]+tcs.depth[z]-max_lca-(min_lca)*2;
            if(tcs.depth[lca1] == tcs.depth[lca2]) cout<<lca3<<" ";
            else if(tcs.depth[lca1] == tcs.depth[lca3]) cout<<lca2<<" ";
            else cout<<lca1<<" ";
            cout<<ans<<endl;
        }
        return;
    }
}
```
</details>

## P4231 三步必杀

### Description

有一个长度为 $n$ 的数组 $a$，初始均为 $0$。有 $q$ 次操作，每次操作四个参数 $l,r,s,e$ 表示将区间 $[l,r]$ 加上一个等差数列，满足首项为 $s$，尾项为 $e$。求 $q$ 次操作后 $\max a_i$ 和 $a$ 数组的异或和。

$n\le 10^7$，limit：500ms 

### Solution

我们做过一个类似的题，叫做 [无聊的数列](https://www.luogu.com.cn/problem/P1438)。回顾一下这个题。

>维护一个数列 $a_i$，支持两种操作：
> - `1 l r K D`：给出一个长度等于 $r-l+1$ 的等差数列，首项为 $K$，公差为 $D$，并将它对应加到 $[l,r]$ 范围中的每一个数上。即：令 $a_l=a_l+K,a_{l+1}=a_{l+1}+K+D\ldots a_r=a_r+K+(r-l) \times D$。
>- `2 p`：询问序列的第 $p$ 个数的值 $a_p$。
>$n,m\le 10^5$。

你会发现上边这个题是 **修改和查询混在一块的**，但这并不妨碍我们差分。每次询问线段树区间查询即可。数据范围较小线段树稳过。

但现在 $n\le 10^7$。时限 500ms，线段树，树状数组都过不了。我们不得不考虑线性做法。

考虑对区间 $[3,6]$ 加上首项为 $2$，公差为 $3$，尾项为 $14$ 的等差数列是什么行为。

```txt
num:1 2 3 4 5 6  7 8
a:  0 2 5 8 11 14 0 0
b:  0 2 3 3 3 3 -14 0
```

这样还是没法维护。诶这不就是给区间 $[2,5]$ 加上公差 $3$ 嘛。我们对 $b$ 进行差分，记作 $c$。

```txt
num:1 2 3 4 5 6  7 8 9
a:  0 2 5 8 11 14 0 0 0
b:  0 2 3 3 3 3 -14 0 0
c:  0 2 1 0 0 0 -17 14 0
```

你会发现 **无论加的等差数列有多长，中间那一串 $0$ 是不变的**。每次操作我们只需修改 $c$ 数组四处即可。

即对于每次操作，我们只需令 $c_l+s,c_{l+1}+(d-s),c_{r+1}-(e+d),c_{r+2}+e$ 即可。

还原数组只需做两遍前缀和即可。这个技巧叫做 **二阶差分**。

<details>
<summary>Code</summary>

```cpp
namespace solution
{
    int n,m;
    int a[N],b[N];
    void solve()
    {
        cin>>n>>m;
        while(m--)
        {
            int l,r,s,e;
            cin>>l>>r>>s>>e;
            int gc = (e-s)/(r-l);
            a[l] += s;
            a[l+1] += (gc-s);
            a[r+1] += (-e-gc);
            a[r+2] += e;
        }
        for(int i=1;i<=n;i++) a[i] += a[i-1];
        int maxn = 0;
        int ans = 0;
        int sum = 0;
        for(int i=1;i<=n;i++)
        {
            sum += a[i];
            ans ^= sum;
            maxn = max(maxn,sum);
        }
        cout<<ans<<" "<<maxn<<endl;
        return;
    }
}
```
</details>

## P6902 [ICPC2014 WF] Surveillance

[Source](https://www.luogu.com.cn/problem/P6902)

### Description

给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的环被完全覆盖的区域数量。

### Solution


**经典模型**

一个经典问题：给定 $k$ 条线段，用最少的线段覆盖长度为 $n$ 的区间。

我们维护线段集合 $S$,当前覆盖到的最右端点 $x$。每次从线段集合中选取左端点小于等于 $x+1$ 右端点最大的线段去覆盖，设该线段有端点为 $y$，令 $x\leftarrow y$。

重复上述操作直到区间全部被覆盖。

**基础模型的简单拓展**

给定 $k$ 条线段，$q$ 次询问，每次询问最少用多少条线段覆盖区间 $[l,r]$。

一个显然的暴力做法是，对于每个询问 $[l,r]$，令 $x=l-1$ 跑上述贪心。

下文定义一轮`greedy select` 为从线段集合中进行一次上述贪心选择。

显然，当起点固定后，进行 $k$ 轮 `greedy select` 后 $x$ 是固定的，毕竟贪心策略一定。

考虑倍增维护每个起点经过若干轮 `greedy select` 后的 $x$。

令 $f_{i,j}$ 为起点为 $i$，经过 $2^j$ 轮 `greedy select` 后的 $x+1$。查询的时候倍增跳即可。

接下来回到本题。

我们断环为链。对于每条线段 $[l,r]$，若 $l>r$，即当前线段是同时跨 $1$ 和 $n$ 的。将 $r+n$。这算是经典做法了。

我们要覆盖环，但不知道从哪开始。这很简单，对于每个点 $i\in[1,n]$ 将其作为起点，倍增跳到 $i+n$ 及以外即可。

至于 $f$ 数组初始化，这么写就行。

```cpp
typedef pair<int,int> PAIR;
PAIR p[N];
//读入和断环为链
sort(p+1,p+1+k);
int r = 0;
for(int i=1,j=1;i<=n*2;i++)
{
    while(j <= k && p[j].x <= i) 
    {
        r = max(r,p[j].y+1);
        j++; 
    }
    f[0][i] = r;
}
```

你会发现实际操作起来和先前对 `greedy select` 的描述不一样。

实际操作时，我们将区间按照左端点排序，对于每个 $i$，只要其左端点小于等于 $i$，就使用线段。并尝试更新 $r$，直到线段左端点不符合条件退出，并更新 $f$ 数组。

对线段按照左端点排序后，随着 $i$ 的右移动，$j$ 的移动是单调的。双指针扫一下就好。

<details>
<summary>参考代码</summary>

```cpp
namespace solution
{
    #define x first
    #define y second
    typedef pair<int,int> PAIR;
    PAIR p[N];
    int f[50][N];
    int n,k;
    void solve()
    {
        cin>>n>>k;
        for(int i=1;i<=k;i++)
        {
            int l,r;
            cin>>l>>r;
            if(l > r) r += n;
            p[i] = {l,r};
        }
        sort(p+1,p+1+k);
        int r = 0;
        for(int i=1,j=1,maxn = 0;i<=n*2;i++)
        {
          // maxn = 0;
            while(j <= k && p[j].x <= i) 
            {
                r = max(r,p[j].y+1);
                j++; 
            }

            f[0][i] = r;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j<=(n*2);j++) f[i][j] = f[i-1][f[i-1][j]];
        int ans = INF;
        for(int i=1;i<=n;i++)
        {
            int x = i,sum = 0;
            for(int j=20;j>=0;j--)
            {
               if(f[j][x] < i+n) 
               {
                    x = f[j][x];
                    sum += (1<<j);
               }
            }
            x = f[0][x];
            sum ++;
            if(x >= i+n) ans = min(ans,sum);
        }
        if(ans == INF) cout<<"impossible"<<endl;
        else cout<<ans<<endl;
        return;
    }
}
```
</details>

## P5021 [NOIP2018 提高组] 赛道修建

### Description

C 城将要举办一系列的赛车比赛。在比赛前，需要在城内修建 $m$ 条赛道。 

C 城一共有 $n$ 个路口，这些路口编号为 $1,2,…,n$，有 $n-1$ 条适合于修建赛道的双向通行的道路，每条道路连接着两个路口。其中，第 $i$ 条道路连接的两个路口编号为 $a_i$ 和 $b_i$，该道路的长度为 $l_i$。借助这 $n-1$ 条道路，从任何一个路口出发都能到达其他所有的路口。 

一条赛道是一组互不相同的道路 $e_1,e_2,…,e_k$，满足可以从某个路口出发，依次经过 道路 $e_1,e_2,…,e_k$（每条道路经过一次，不允许调头）到达另一个路口。一条赛道的长度等于经过的各道路的长度之和。为保证安全，要求每条道路至多被一条赛道经过。 

目前赛道修建的方案尚未确定。你的任务是设计一种赛道修建的方案，使得修建的 $m$ 条赛道中长度最小的赛道长度最大（即 $m$ 条赛道中最短赛道的长度尽可能大）

![img](https://img2023.cnblogs.com/blog/3195128/202408/3195128-20240824111143010-1021371948.png)

### Solution

妙妙题。

题目保证了 **有 $n-1$ 条道路，且图连通**，这是一棵树。

注意到 “求长度最小的赛道长度最大值”。这是 “最小值最大” 问题，我们可以二分，把最优化问题转换为判定性问题。

作为当年 noip T3 ~~防 ak 题~~ ，肯定给了充足的部分分。表格如上。

首先考虑当 $m=1$，只修建一条赛道，求树的直径即可。

当 $a_i=1$时，图为菊花图，由于 **不可走回头路**，路径最多有两条边。对于每条边，若 $\ge mid$，令其单独为一条路径。将所有 $< mid$ 的边存入集合 $S$，对其升序排序，双指针匹配即可。

当 $b_i=a_i+1$ 时，是一条链。模拟扫一遍即可。

做完上述部分分可获得 $11\times 5=55$ 的好成绩！考场上能拿 55 pts 已经 win 了。

接下来考虑正解。

我们考虑树上的一条路径长什么样子。设路径两端点为 $(u,v)$，要么路径 $u.v$ 是一条链，要么路径为 $u\rightarrow \text{LCA}(u,v)\rightarrow v$。在树上，对于任意节点 $u$（除根节点外），有且仅有一个父亲 $fa_u$。故考虑 $u$ 对 $fa_u$ 的贡献。

定义 $f_v$ 为以 $v$ 为链头，最大的未匹配上赛道的链长。$fa_v=u$。边 $(u,v)$ 的边权为 $w$。

- 若 $f_v+w \ge mid$，令答案 $+1$。直接匹配。

- 反之，点 $u$ 可能是赛道两端点的 $\text{LCA}$。将信息记录，准备后续匹配。

当 $u$ 的所有儿子 $v$ 都遍历完，回溯的时候，我们对先前记录的信息进行匹配。匹配的时候贪心的匹配最小的。枚举每个 $f_v+w$，若无法匹配，尝试更新 $f_u$。反之，匹配上了不可更新 $f_u$。

对于每个 $f_v+w$，如何找到最小的与其匹配的呢？用 mutiset 即可。自动排序。不能用 set 因为重复的元素会全部删掉。当然优先队列也行。

上述匹配过程是一个树形 dp 的过程。

代码很简单。

### Code

```cpp
namespace solution
{
    typedef pair<int,int> PAIR;
    int n,m;
    int p,res;
    vector <PAIR> Edge[N];
    int siz[N];
    int f[N];
    void dfs(int u,int fa)
    {
        #define x first
        #define y second
        set <int> s;
        for(auto t:Edge[u])
        {
            int v = t.x,w = t.y;
            if(v == fa) continue;
            dfs(v,u);
            if(f[v] + w >= p) res ++;
            else s.insert(f[v] + w);
        }
        while(!s.empty())
        {
            set <int>::iterator it = s.begin();
            s.erase(it);
            set <int>::iterator it1 = s.lower_bound(p-*it);
            if(it1 == s.end()) f[u] = max(f[u],*it);
            else {res ++;s.erase(it1);}
        }
    }
    bool check(int k)
    {
        p = k;
        res = 0;
        fill(f+1,f+n+1,0);
        dfs(1,0);
        return res >= m;
    }
    void solve()
    {
        cin>>n>>m;
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            Edge[u].push_back(PAIR(v,w));
            Edge[v].push_back(PAIR(u,w));
        }
        int l=0,r = INF;
        int answer;
        while (l<=r)
        {
            int mid = (l+r) >> 1;
            if(check(mid)) {l = mid+1;answer = mid;}
            else r = mid - 1;
        }
        cout<<answer<<endl;
    }
}
```


## P4211 [LNOI2014] LCA

[Source](https://www.luogu.com.cn/problem/P4211)

### Description

给出一个 $n$ 个节点的有根树（编号为 $0$ 到 $n-1$，根节点为 $0$）。
一个点的深度定义为这个节点到根的距离 $+1$。 
设 $dep[i]$ 表示点 $i$ 的深度，$\operatorname{LCA}(i, j)$ 表示 $i$ 与 $j$ 的最近公共祖先。 
有 $m$ 次询问，每次询问给出 $l, r, z$，求 $\sum_{i=l}^r dep[\operatorname{LCA}(i,z)]$ 。

$1\le n\le 5\times 10^4$。

### Solution

每次询问求区间内的所有数和 $z$ 的 $\text{LCA}$ 的深度。$u$ 的深度即为 $u$ 到 $root$ 路径上经过点的数量。以此类推，两点 $\text{LCA}$ 的深度即为两点到 $root$ 路径的公共部分。因此，对于 $\forall i\in\{l,r\}$，将其到 $root$ 路径上所有点权 $+1$，最后求 $root$ 到 $z$ 路径权值即可。树链剖分 + 线段树即可解决问题。

但这样复杂度太高了。

注意到区间 $[1,r]$ 和区间 $[1,r+1]$ 有大量重复部分。若将每次询问独立，每次清空线段树再重新 modify,就很慢。不妨将询问离线，按照右端点排序（左端点都是 $1$）。
区间 $[l,r]$ 对 $z$ 的贡献可以拆成区间 $[1,r]$ 对 $z$ 的贡献减去区间 $[1,l-1]$ 对 $z$ 的贡献。将区间 $[1,l-1],[1,r]$ 扔到集合 $S$ 中，对集合 $S$ 按照右端点排序。

对于每个拆分后的区间，在上一个下标 $pos$ 基础上进行 modify。同时进行查询，若当前区间是 $[1,l-1]$，该询问答案减去 query 值，否则加。在拆区间的同时记录一下即可。

不会在线做法。

<details>
<summary>参考代码</summary>

```cpp
constexpr int N = 1000010;
constexpr int mod = 201314;
namespace solution
{
    int n,m;
    int ans[N];
    vector <int> Edge[N];
    struct Node
    {
        int pos,z,id,flg;
        bool operator<(const Node& a)const{
            return pos < a.pos;
        }
    };
    vector <Node> q;
    struct segtree
    {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N],tag[N];
        void pushdown(int p,int len)
        {
            if(!tag[p]) return;
            tree[ls] += (len-len/2)*tag[p],tree[rs] += (len/2)*tag[p];
            tag[ls] += tag[p],tag[rs] += tag[p];
            tag[p] = 0;
        }
        void pushup(int p){tree[p] = tree[ls] + tree[rs];}
        void modify(int l,int r,int pl,int pr,int p,int d)
        {
            if(l > pr || r < pl) return;
            if(l >= pl && r <= pr) {tree[p] += (r-l+1)*d;tag[p] += d;return;}
            int mid = (l+r) >> 1;
            pushdown(p,r-l+1);
            modify(l,mid,pl,pr,ls,d);
            modify(mid+1,r,pl,pr,rs,d);
            pushup(p);
        }
        int query(int l,int r,int pl,int pr,int p)
        {
            if(l > pr || r < pl) return 0;
            if(l >= pl && r <= pr) return tree[p];
            int mid = (l+r) >> 1;
            pushdown(p,r-l+1);
            return query(l,mid,pl,pr,ls) + query(mid+1,r,pl,pr,rs);
        }
    }seg;
    struct TCS
    {
        int dfn[N],siz[N],depth[N],son[N],tp[N],fa[N];
        int cnt = 0;
        void dfs1(int u,int f)
        {
            depth[u] = depth[f] + 1;
            siz[u] = 1;
            fa[u] = f;
            int maxn = 0,maxx = 0;
            for(auto v:Edge[u])
            {
                if(v == f) continue;
                dfs1(v,u);
                siz[u] += siz[v];
                if(siz[v] > maxn)
                {
                    maxn = siz[v];
                    maxx = v;
                }
            }
            son[u] = maxx;
        }
        void dfs2(int u,int topp)
        {
            dfn[u] = ++cnt;
            tp[u] = topp;
            if(!son[u]) return;
            dfs2(son[u],topp);
            for(auto v:Edge[u])
            {
                if(v == fa[u] || v == son[u]) continue;
                dfs2(v,v);
            }
        }
        void modify(int x,int y,int d)
        {
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                seg.modify(1,n,dfn[tp[y]],dfn[y],1,d);
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            seg.modify(1,n,dfn[x],dfn[y],1,d);
            return;
        }
        int query(int x,int y)
        {
            int sum = 0;
            while(tp[x] != tp[y])
            {
                if(depth[tp[x]] > depth[tp[y]]) swap(x,y);
                sum += seg.query(1,n,dfn[tp[y]],dfn[y],1);
                y = fa[tp[y]];
            }
            if(depth[x] > depth[y]) swap(x,y);
            sum += seg.query(1,n,dfn[x],dfn[y],1);
            return sum;
        }
    }tcs;
    void solve()
    {
        cin>>n>>m;
        for(int i=2;i<=n;i++) 
        {
            int f;
            cin>>f;
            f ++;
            Edge[f].push_back(i);
            Edge[i].push_back(f);
        }
        tcs.dfs1(1,0);
        tcs.dfs2(1,0);
        for(int i=1;i<=m;i++)
        {
            int l,r,z;
            cin>>l>>r>>z;
            l ++;
            r ++;
            z ++;
            q.push_back({l-1,z,i,0});
            q.push_back({r,z,i,1});
        }
        sort(q.begin(),q.end());
        int pos = 1;
        for(auto t:q)
        {
            while(pos <= t.pos) tcs.modify(1,pos++,1);
            if(t.flg) ans[t.id] += tcs.query(1,t.z);
            else ans[t.id] -= tcs.query(1,t.z);
            ans[t.id] += mod;
            ans[t.id] %= mod;
        }
        for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
        return;
    }
}
```
</details>