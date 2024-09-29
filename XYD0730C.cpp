#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
constexpr int N = 1000010;
int qwq[N];
int a[N];
int n;
int ans = 0;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
 //   int l = r = 1;
    int ok = 0,number = 0;
    for(int l =1,r = 1;r <= n ;r++)
    {
       
        if(!qwq[a[r]]) number ++;
        qwq[a[r]] ++;
        bool flag = 0;
        while(qwq[a[r]] > 2 && l <= r) 
        {
            flag =1;
             
            if(qwq[a[l]] == 2) ok --;
            qwq[a[l]]--;
            //if(qwq[a[l]] == 2) ok ++;
            if(!qwq[a[l]]) number --;
            l ++;
           
        } 
        if(!flag)
            if(qwq[a[r]] == 2) ok ++; 
      //  cout<<"["<<l<<","<<r<<"]:"<<number<<" "<<ok<<endl;
        if(number == ok) 
        {
          //  cout<<number<<" "<<ok<<endl;
            cout<<l<<" "<<r<<endl;
            ans ++;
        }
    }
    cout<<ans<<endl;
    return 0;
}