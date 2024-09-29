#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int N = 1010;
size_t T;
size_t n,m;
char mapp[N][N];
void print()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++) cout<<mapp[i][j];
        cout<<endl;
    }
    return;
}
void solve()
{
    for(int i=0;i<n;i++)
    {
        bool flag = 1;
        for(int j=0;j<m;j++) 
        { 
            if(i % 3 == 0)
            {
                mapp[i][j] = 'X';
                if(flag && mapp[i-1][j] == 'X')
                {
                    mapp[i-1][j] = mapp[i-2][j] = 'X';
                    flag = 0;
                }
                if(flag && i > 1 && mapp[i-2][j] == 'X')
                {
                    mapp[i-1][j] = mapp[i-2][j] = 'X';
                    flag = 0;
                }
            }
            else if(i == n-1)
            {
                if(mapp[i][j] == 'X')
                {
                    if(i > 0) mapp[i-1][j] = 'X';
                }
            }
        } 
        if(flag && i % 3 == 0 && i > 0) mapp[i-1][0] = mapp[i-2][0] = 'X';
    }
    print();
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        for(int i=0;i<n;i++) 
        {
            for(int j=0;j<m;j++) cin>>mapp[i][j];
        }
        solve();
    }
}