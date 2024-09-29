#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
size_t n;
size_t T;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--)
    {
        cin>>n;
        if(n == 1) {cout<<"1\n";continue;}
        for(int i=0;i<n/2;i++)
            cout<<"1"<<string(i,'0')<<"6"<<string(i,'0')<<"9"<<string(n-3-i*2,'0')<<endl;
        for(int i=0;i<n/2;i++)
            cout<<"9"<<string(i,'0')<<"6"<<string(i,'0')<<"1"<<string(n-3-i*2,'0')<<endl;
        cout<<"196"<<string(n-3,'0')<<endl;
    }
}