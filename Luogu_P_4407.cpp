#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 25;
constexpr int p = 31;
int n,m,len,ans,cnt;
size_t pp[N],l[N],r[N],h[N];
unordered_map<size_t,size_t> a[N],b[N][N],c[N];
char s[N];
char qwq[N];
int main()
{
    scanf("%d%d",&n,&m);
    pp[0] = 1;
    for(int i=1;i<=25;i++) pp[i] = pp[i-1]*p;
    for(int i=1;i<=n;i++)
    {
        
        scanf("%s",s+1);
        int len = strlen(s+1);
        for(int j=0;j<25;j++) l[j] = r[j] = h[j] = 0;
        for(int j=1;j<=len;j++) l[j] = l[j-1]*p+(s[j]-'a'+1);
        for(int j = len;j>=1;j--) r[j] = r[j+1]+(s[j]-'a'+1)*pp[len-j];
        a[len][l[len]] ++;
        for(int j=1;j<=len;j++)
        {
            h[j] = l[j-1]*pp[len-j]+r[j+1];
            b[len-1][j][h[j]] ++;
        }
        sort(h+1,h+1+len);
        cnt = 1;
        for(int j=2;j<=len;j++)
            if(h[j] != h[j-1]) h[++cnt] = h[j];
        for(int j=1;j<=cnt;j++) c[len-1][h[j]] ++;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s",qwq+1);
        len = strlen(qwq+1);
        for(int j=0;j<=25;j++) l[j] = r[j] = h[j] = 0;
        for(int j=1;j<=len;j++) l[j] = l[j-1]*p+(qwq[j]-'a'+1);
        for(int j=len;j>=1;j--) r[j] = r[j+1]+(qwq[j]-'a'+1)*pp[len-j];
        if(a[len][l[len]])
        {
            printf("-1\n");
            continue;
        }
        ans = 0;
        for(int j=1;j<=len;j++) h[j] = l[j-1]*pp[len-j]+r[j+1];
        for(int j=1;j<=len;j++) ans += b[len-1][j][h[j]];
       sort(h+1,h+1+len);
        cnt = 1;
        for(int j=2;j<=len;j++) 
        {
            if(h[j] != h[j-1]) h[++cnt] = h[j];

        }
        for(int j=1;j<=cnt;j++) ans += a[len-1][h[j]];
        ans += c[len][l[len]];
        printf("%d\n",ans);
    }
    return 0;
}