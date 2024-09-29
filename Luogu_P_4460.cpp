#include <bits/stdc++.h>
#include <bits/extc++.h>
#define x first
#define y second
#define size_t long long
#define eqs 1e-7
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1000010;
constexpr int mod = 1e5-7;
constexpr int INF = 0x3f3f3f3f;
typedef pair<int,int> PAIR;
size_t n,ans;
PAIR p[N];
size_t g[N][25];
size_t f[N][25];
size_t popc[N];
bool get(PAIR a,PAIR b,PAIR c)
{
    	return (a.x-b.x)*(b.y-c.y)==(b.x-c.x)*(a.y-b.y);
}
size_t popcount(size_t x)
{
    size_t answer = 0;
    while(x)
    {
        answer ++;
        x &= (x-1);
    }
   // cout<<answer<<endl;
    return answer;
}
bool cmp(PAIR a,PAIR b) {return a.x < b.x || (a.x == b.x && a.y < b.y);}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
 	for(int i=1;i<(1<<n);i++)
		popc[i]=popc[i>>1]+(i&1);
    //sort(p+1,p+n+1,cmp);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i == j) continue;
            for(int k=0;k<n;k++)
            {
                if(k == i || k == j) continue;
            //    cout<<abs(get(p[i].x,p[i].y,p[k].x,p[k].y)-get(p[k].x,p[k].y,p[j].x,p[j].y))<<endl;
                    if(((p[k].x-p[i].x)*(p[k].x-p[j].x)<0||(p[k].y-p[i].y)*(p[k].y-p[j].y)<0)&&get(p[i],p[k],p[j]))
                        g[i][j] |= (1<<k);
            }
        }
    }
    for(int i=0;i<n;i++)
        f[1<<i][i] = 1;
 	for(int i=1;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
			if(f[i][j]&&((1<<j)&i))
			{
				if(popc[i]>=4)ans=(ans+f[i][j])%mod;
				for(int k=0;k<n;k++)
					if(!((1<<k)&i)&&(g[j][k]&i)==g[j][k])
					{
						f[i|(1<<k)][k]=(f[i|(1<<k)][k]+f[i][j])%mod;
					}
			}
	}
 //   cout<<f[2][1]<<endl;
  //  cout<<n<<endl;
  //  size_t ans =0;
//     for(int i=0;i<(1<<(n+1));i++)
//     {
//       //  cout<<i<<endl;
//         if(popc[i] >= 4) 
//         {
//                     for(int j=1;j<=n;j++) 
//         {
//    //         cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
//             if(i&(1<<j)) ans = (ans + f[i][j])%mod;
//         }
//         }

//     }
    cout<<ans<<endl;
    return 0;
}