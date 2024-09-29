
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 100010;
int n,m;
int a[N];
int p[N],q[N];
// #define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  template <class T>
  void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
  }

  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) { for (c = gc(); blank(c); c = gc()); }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  // 负数输出
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }

  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
int main()
{
   // freopen("hot.in","r",stdin);
  //  freopen("hot.out","w",stdout);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
  fread(n);
  fread(m);
    for(int i=1;i<=n;i++) fread(a[i]);
    p[n] = n+1;
    q[n] = n+1;
    for(int i=n-1;i>=1;i--)
    {
        if(a[i] > a[i+1]) 
            p[i] = i;
        else p[i] = p[i+1];
        if(a[i] < a[i+1]) q[i] = i;
        else q[i] = q[i+1];
    }
    while(m--)
    {
        int l,r;
        cin>>l>>r;
        if(p[l] >= r) {fwrite("Y")}
        else 
        {
            if(q[p[l]] >= r) {puts("Y\n");}
            else {puts("N\n");}
        }
    }
    return 0;
}