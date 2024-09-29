#include <bits/stdc++.h>
using namespace std;
namespace solution
{
    bool is_num(char ch){return ch >= '0'&& ch <= '9';}
    void solve(string str)
    {
        int sum = 0;
        bool have_num = 0;
        for(int i=0;i<str.size();i++)
        {
            cerr<<i<<endl;
            if(is_num(str[i])) have_num = 1;
            if(str[i] == '-')
            {
                if(is_num(str[i-1])) {continue;} // 若负号前面是数字，当数字之间间隔处理
                string get_n;
                get_n.clear();
                int num = 0;
                i ++;
                while(is_num(str[i]) && i < str.size()) // 获取数字
                {
                    have_num = 1;
                    num = num*10 +(str[i]-'0');
                    i ++;
                }
                i--;  // 注意：前面为了获取负号后面的数字，执行了 i++，若不执行这一行遇到 1---1 数据会忽略负号 
                sum += (-num);
            }
            else 
            {
                //cerr<<i<<endl;
                nxt:
                int num = 0;
                while(is_num(str[i]) && i < str.size())
                {
                 //   cerr<<i<<endl;
                    have_num = 1;
                    num = num * 10 + (str[i] - '0');
                    i ++;
                }
            //    i--; // 防止死循环。跳过一个非数字也没关系，如果跳过了负号也没事。
                sum += num;
            }
        }
        if(!have_num) return;
        cout<<sum<<endl;
        return;
    }
    void mian()
    {
        string qwq;
        while(getline(cin,qwq)) solve(qwq); 
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::mian();
    return 0;
}