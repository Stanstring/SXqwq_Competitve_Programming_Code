#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1010;
int n;
double d1,d2,c,p,d[N],v[N],last,ans;
int main()
{
    cin>>d1>>c>>d2>>p>>n;
    for(int i=1;i<=n;i++) cin>>d[i]>>v[i];
    d[n+1] = d1,v[0] = p;
    for(int i=1;i<=n;i++) 
    {
        if(d[i+1]-d[i] > c*d2)
        {
            cout<<"No Solution\n"<<endl;
            return 0;
        }
    }
    int jj;
    for(int i=0;i<=n;i=jj)
    {
        for(jj = i+1;jj<=n+1;jj++)
        {
            if(d[jj]-d[i] > c*d2)
            {
                jj--;
                break;
            }
            if(v[jj] < v[i]) break;
        }
         if(v[jj] < v[i])
         {
            ans += ((d[jj]-d[i])/d2-last)*v[i];
            last = 0;
         }
         else 
         {
            ans += (c-last)*v[i];
         last = c-(d[jj]-d[i])/d2;
         }
    }
    printf("%.2lf\n",ans);
    return 0;
}