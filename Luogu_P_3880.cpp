#include <bits/stdc++.h>
using namespace std;
namespace solution
{
    int lst = 0;
    bool is_char(char x) {return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');}
    bool is_y(string s)
    {
        for(int i=0;i<s.size();i++) s[i] = toupper(s[i]);
        for(int i=0;i<s.size();i++) if((s[i] == 'A' || s[i] == 'E' || s[i] =='I' || s[i] == 'O' || s[i] == 'U') && i > lst) return 1;
        return 0;
    }
    void solve()
    {
        string str;
        getline(cin,str);
        string str1 = str,str2 = str,str3 = str;
        for(int i=0;i<str1.size();i++) if(is_char(str1[i])) str1[i] = '.';
        cout<<str1<<endl;
        int num = 0;
        for(int i=0;i<str2.size();i++)
            if(is_char(str2[i])) num ++;
        double k = round(num*1.0/3);
        for(int i=0;i<str.size();i++)
        {
            if(is_char(str2[i]))
            {
                if(k) 
                {
                    lst = i;
                    k --;
                }
                else str2[i] = '.';
                cout<<str2[i];
            }
            else cout<<str2[i];
        }
        cout<<endl;
        if(is_y(str))
        {
            for(int i=0;i<str.size();i++)
            {
                if(is_char(str[i]))
                {
                    if(i <= lst) cout<<str[i];
                    else
                    {
                        char t = str[i];
                        t = toupper(t);
                        if(t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') cout<<str[i];
                        else cout<<".";
                    }
                   
                } 
                else cout<<str[i];
            }
        }
        else 
        {
            double t = round(num*2*1.0/3);
            for(int i=0;i<str.size();i++)
            {
                if(is_char(str[i]))
                {
                    if(t){ cout<<str[i],t--;}
                    else cout<<".";
                }
                else cout<<str[i];
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution::solve();
}