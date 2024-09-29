#include<bits/stdc++.h>
#define N 400001
#define len 200000
using namespace std;

int n, m, la, mi, b, ans, lm;
int a[N], tree[N << 2], tag[N << 2];
char s[10];

void pushup(int rt)
{
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void change(int rt, int l, int r, int x, int y)//单点修改
{
    if(l == r)
    {
        tree[rt] += y;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(rt << 1, l, mid, x, y);
    else change(rt << 1 | 1, mid + 1, r, x, y);
    pushup(rt);
}

int query(int rt, int l, int r, int x, int y)//求值域内的数量
{
    if(x <= l && r <= y) return tree[rt];
    int mid = (l + r) >> 1, res = 0;
    if(x <= mid) res += query(rt << 1, l, mid, x, y);
    if(y > mid) res += query(rt << 1 | 1, mid + 1, r, x, y);
    return res;
}

int js(int rt, int l, int r, int x)//求第k大
{
//    cerr<<mi<<endl;
    if(l == r) return l;
    int mid = (l + r) >> 1, l1 = -1, r1 = -1;
    if(mi < l) l1 = tree[rt << 1];
    else if(l <= mi && mi <= mid) l1 = query(rt << 1, l, mid, mi, mid);
    else if(mid < mi && mi <= r) r1 = query(rt << 1 | 1, mid + 1, r, mi, r);
    else r1 = tree[rt << 1 | 1];
    //左边数量与右边数量
    if(r1 == -1) r1 = tree[rt] - l1;
    l1 = tree[rt] - r1;
    if(r1 >= x) return js(rt << 1 | 1, mid + 1, r, x);
    else return js(rt << 1, l, mid, x - r1);
}

void ql(int rt, int l, int r, int x, int y)//清零操作
{
    if(l == r)
    {
        tree[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid && tree[rt << 1]) ql(rt << 1, l, mid, x, y);
    if(y > mid && tree[rt << 1 | 1]) ql(rt << 1 | 1, mid + 1, r, x, y);
    pushup(rt);
}

int main()
{
    scanf("%d%d", &n, &m), lm = m, m += len;
    for(int i = 1; i <= n; i++)
    {
        int x;
        scanf("%s%d", s, &x);
        if(s[0] == 'I')
        {
            if(x < lm) continue;
            change(1, 0, N - 1, x - b + len, 1);//加入员工
        }
        else if(s[0] == 'A') m -= x, b += x;//增加工资
        else if(s[0] == 'S')
        {
            m += x, b -= x;
            if(m >= 1 && query(1, 0, N - 1, 0, m - 1) > 0) ans += query(1, 0, N - 1, 0, m - 1), ql(1, 0, N - 1, 0, m - 1);//踢出员工
        }
        else
        {
            if(x > query(1, 1, N - 1, m, N - 1)) puts("-1");//工资大于k的数量
            else printf("%d\n", js(1, 0, N - 1, x) + b - len);
        }
    }
    printf("%d\n", ans);
    return 0;
}