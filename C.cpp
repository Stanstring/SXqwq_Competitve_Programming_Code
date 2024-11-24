#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1e5 + 10;

namespace FastIO {
    char buf[1 << 21], *p1 = buf, *p2 = buf;
    #define getchar() (p1 == p2 && (p1 = buf, p2 = (p1 + fread(buf, 1, 1 << 21, stdin))) == p1 ? EOF : *p1++)
    template <typename T>
    inline T read() {
        T x = 0, w = 0;
        char ch = getchar();
        while (ch < '0' || ch > '9')
            w |= (ch == '-'), ch = getchar();
        while ('0' <= ch && ch <= '9')
            x = x * 10 + (ch ^ '0'), ch = getchar();
        return w ? -x : x;
    }
    template <typename T>
    inline void write(T x) {
        if (!x) return;
        write<T>(x / 10), putchar((x % 10) ^ '0');
    }
    template <typename T>
    inline void print(T x) {
        if (x > 0)
            write<T>(x);
        else if (x < 0)
            putchar('-'), write<T>(-x);
        else
            putchar('0');
    }
    template <typename T>
    inline void print(T x, char en) {
        print<T>(x), putchar(en);
    }
}
using namespace FastIO;

namespace solution {
    int n, q;
    int a[N];

    struct segtree2 {
        struct Node {
            vector<int> vals;
            vector<long long> sums;
        } tree[N * 4];

        void build(int node, int l, int r) {
            tree[node].vals.clear();
            tree[node].sums.clear();
            if (l == r) {
                tree[node].vals.push_back(a[l]);
                tree[node].sums.push_back(a[l]);
                return;
            }
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            merge(tree[node * 2].vals.begin(), tree[node * 2].vals.end(),
                  tree[node * 2 + 1].vals.begin(), tree[node * 2 + 1].vals.end(),
                  back_inserter(tree[node].vals));
            long long sum = 0;
            for (int val : tree[node].vals) {
                sum += val;
                tree[node].sums.push_back(sum);
            }
        }

        long long query(int node, int l, int r, int ql, int qr, int x) {
            if (qr < l || ql > r) {
                return 0;
            }
            if (ql <= l && r <= qr) {
                int k = lower_bound(tree[node].vals.begin(), tree[node].vals.end(), x) - tree[node].vals.begin();
                if (k == 0) return 0;
                return tree[node].sums[k - 1];
            }
            int mid = (l + r) / 2;
            return query(node * 2, l, mid, ql, qr, x) +
                   query(node * 2 + 1, mid + 1, r, ql, qr, x);
        }
    } seg2;

    struct segtree1 {
        vector<int> tree[N * 4];

        void build(int node, int l, int r) {
            if (l == r) {
                tree[node].push_back(a[l]);
                return;
            }
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            merge(tree[node * 2].begin(), tree[node * 2].end(),
                  tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(),
                  back_inserter(tree[node]));
        }

        int query(int node, int l, int r, int ql, int qr, int x) {
            if (qr < l || ql > r) {
                return 0;
            }
            if (ql <= l && r <= qr) {
                return lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
            }
            int mid = (l + r) / 2;
            return query(node * 2, l, mid, ql, qr, x) +
                   query(node * 2 + 1, mid + 1, r, ql, qr, x);
        }
    } seg1;

    struct segtree {
        #define ls p<<1
        #define rs p<<1|1
        int tree[N * 4];

        void pushup(int p) {
            tree[p] = tree[ls] + tree[rs];
        }

        void build(int l = 1, int r = n, int p = 1) {
            if (l == r) {
                tree[p] = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(l, mid, ls);
            build(mid + 1, r, rs);
            pushup(p);
        }

        int query(int l, int r, int pl, int pr, int p) {
            if (l >= pl && r <= pr) return tree[p];
            int mid = (l + r) >> 1, sum = 0;
            if (pl <= mid) sum += query(l, mid, pl, pr, ls);
            if (pr > mid) sum += query(mid + 1, r, pl, pr, rs);
            return sum;
        }
    } seg;

    void solve() {
        n = read<int>();
        q = read<int>();
        for (int i = 1; i <= n; i++) {
            a[i] = read<int>();
        }
        seg.build();
        seg1.build(1, 1, n);
        seg2.build(1, 1, n);
        while (q--) {
            int l, r;
            l = read<int>();
            r = read<int>();
            int sum = seg.query(1, n, l, r, 1);
            int len = r - l + 1;
            int average = sum / len;
            int smaller_sum = seg2.query(1, 1, n, l, r, average);
            int smaller_cnt = seg1.query(1, 1, n, l, r, average);
            int ans = average * smaller_cnt - smaller_sum;
            ans += (sum - smaller_sum) - average * (len - smaller_cnt);
            print(ans, '\n');
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
    return 0;
}