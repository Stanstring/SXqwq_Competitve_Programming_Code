#include <bits/stdc++.h>
using namespace std;
string s;
int n,t;
map <string,int> m;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>t;
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s.size() < t)
        {
            cnt ++;
            continue;
        }
        string qwq;
        qwq.clear();
        int qaq = s.size()-t;
        if(qaq < 0) qaq = 0;
        for(int j=s.size()-1;j>=qaq;j--) qwq += s[j];
        reverse(qwq.begin(),qwq.end());
      //  cout<<qwq<<endl;
        map <string,int>::iterator it;
        it = m.find(qwq);
        if(it == m.end())
        {
            cnt ++;
            m[qwq] = 1;
        }
    }
    cout<<cnt<<endl;
    return 0;
}